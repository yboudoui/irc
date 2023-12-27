/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner_mode.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/27 17:30:07 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wagner.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string>

void	Channel::ProcessModeCmd(User* user, const std::string& cmd, t_params& params)
{
	char op = '+';
	for (size_t i = 0; i < cmd.size(); ++i)
	{
        char c = cmd[i];

            switch (c) {
                case '+' :
                case '-' :
                    op = c;
                    break;
                case 'i':
                    this->setMode(op, INVITE_ONLY);
                    break;
                case 't':
                     this->setMode(op, TOPIC_ONLY_OP);
                    break;
                case 'k':
                    if (params.empty() && op == '+')
                    {
                        user->setSendCache(ERR_NEEDMOREPARAMS(name.get(), "MODE", "please type a password (+k)"));
                       break;
                    }
                    if (this->getMode(KEY_PROTECTED) && op == '+')
                    {
                        user->setSendCache(ERR_KEYSET(user->nick_name.get(), name.get()));
                       break;  
                    }
                    if (op == '+')
                    {
                        std::string pass = *params.begin();
                        params.pop_front();
                        if (pass.find_first_not_of("abcdefghijklmnopqrstuvwxyz01234A56789"))
                        {
                            this->setMode(op, KEY_PROTECTED);
                            this->setKey(pass);
                        }
                        else 
                            user->setSendCache(ERR_KEYSET(user->nick_name.get(), name.get(), "please type an alnum password"));
                    }
                    else
                        this->setMode(op, KEY_PROTECTED);
                    break;
                case 'l' :
                    if (params.empty() && op == '+')
                    {
                        user->setSendCache(ERR_NEEDMOREPARAMS(name.get(), "MODE", "please type user limit (+l)"));
                       break;
                    }
                    if (op == '+')
                    {
                        std::string s_limit = *params.begin();
                        params.pop_front();
                        if (s_limit.find_first_not_of("0123456789"))
                        {
                            size_t _limit;
                            std::stringstream ss;
                            ss << s_limit;
                            ss >> _limit;
                            this->setMode(op, USER_LIMIT);
                            this->limit.set(_limit);
                        }
                        else 
                            user->setSendCache(ERR_NEEDMOREPARAMS(name.get(), "MODE", "please type a numeric user limit (+l)"));
                    }
                    else 
                    {
                        this->setMode(op, USER_LIMIT);
                    }
                    break;
                case 'o':
                    if (params.empty())
                    {
                        user->setSendCache(ERR_NEEDMOREPARAMS(name.get(), "MODE", "please type a nickname (o)"));
                        break;
                    }
					{
					std::string	s_ChannelUser = params.front();
					params.pop_front();

					available<t_client>	client = find_by(nickName(s_ChannelUser));
					if (client == false)
						user->setSendCache(ERR_NOSUCHNICK(name.get(), s_ChannelUser));
					else
					{
						if (client().first == user)
							break;
						_users_map.find(client().first)->second = OPERATOR;
					}
					}
                    break;
                
                default:
                    user->setSendCache(ERR_UNKNOWNMODE(name.get(), c));
                    break;
            }
        
    }
}

void	Wagner::cmd_mode(void)
{
	DEBUG_CALL_WAGNER
	if (!user->isConnected())
		return (user->setSendCache(ERR_NOTREGISTERED()));

	if (request->params.size() < 1 )
		return (user->setSendCache(ERR_NEEDMOREPARAMS("", "MODE")));
    
    std::string s_channel, s_modes;
    s_channel = *request->params.begin();
    request->params.pop_front();
    
    if (!s_channel.empty() && s_channel[0] == '#')
        s_channel = s_channel.substr(1);
    Channel* channel = find_channel(s_channel);
    if (!channel)
    {
        if (!findClient(s_channel))
            user->setSendCache(ERR_NOSUCHCHANNEL(user->nick_name.get(), s_channel));
//        else
 //           user->setSendCache(ERR_UMODEUNKNOWNFLAG(user->nick_name.get()));
        return ;
    }
    if (!channel->isInChannel(user))
    {
        user->setSendCache(ERR_NOTONCHANNEL(user->nick_name.get(), s_channel));
        return ;
    }
    if (!request->params.empty())
    {
        if (!channel->isOperator(user))
        {
            user->setSendCache(ERR_CHANOPRIVSNEEDED(user->nick_name.get(), s_channel));
            return ;
        }
        s_modes = *request->params.begin();
        request->params.pop_front();
        channel->ProcessModeCmd(user, s_modes, request->params);
    }
    user->setSendCache(RPL_CHANNELMODEIS(user->nick_name.get(), channel));
}


/*
Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]
 
If a user attempts to make themselves an operator using the "+o"
flag, the attempt should be ignored.  There is no restriction,
however, on anyone `deopping' themselves (using "-o").  Numeric
Replies:

ERR_NEEDMOREPARAMS (461)
<command> :<reason>  
Returned by the server by any command which requires
more parameters than the number of parameters given 

ERR_CHANOPRIVSNEEDED (482) 
<channel> :<reason> 
Returned by any command requiring special channel 
privileges (eg. channel operator) to indicate 
the operation was unsuccessful

ERR_NOTONCHANNEL (442) 
<channel> :<reason>   Returned by the server 
whenever a client tries to perform a channel 
effecting command for which the client is not a member

RPL_BANLIST (367) 
<channel> <banid> [<time_left> :<reason>]
 ban-list item (See RFC); <time left> and <reason> are additions used by KineIRCd

RPL_ENDOFBANLIST (368)
<channel> :<info>
Termination of an RPL_BANLIST list 

ERR_UNKNOWNMODE (472)
<char> :<reason>
Returned when a given mode is unknown

RPL_CHANNELMODEIS (324)
<channel> <mode> <mode_params>

ERR_NOSUCHNICK (401)
<nick> :<reason> 
Used to indicate the nickname parameter supplied 
to a command is currently unused 

ERR_KEYSET (467)
<channel> :<reason>
Returned when the channel key for a 
channel has already been set

ERR_NOSUCHCHANNEL (403)
<channel> :<reason> 
Used to indicate the given channel name is invalid, or does not exist

ERR_USERSDONTMATCH (502)
:<reason> 
Error sent to any user trying to view or 
change the user mode for a user other than themselves

RPL_UMODEIS (221)
<user_modes> [<user_mode_params>]
Information about a user's own modes. Some daemons have extended the mode command and certain modes take parameters (like channel modes). 
*/
