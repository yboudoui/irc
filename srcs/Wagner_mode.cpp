/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner_mode.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 08:21:11 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wagner.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string>

bool	Channel::ProcessModeCmd(User* user, const std::string& cmd, t_params& params)
{
	std::string reply;
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
					modes = (op == '+') ? modes | INVITE_ONLY : modes & ~INVITE_ONLY;
                    reply = ":" + user->nick_name.get() + " MODE #" + this->name + " " + op + "i\r\n";
                    this->sendToAllUsers(reply);
                    break;
                case 't':
					modes = (op == '+') ? modes | TOPIC_ONLY_OP : modes & ~TOPIC_ONLY_OP;
                    reply = ":" + user->nick_name.get() + " MODE #" + this->name + " " + op + "t\r\n";
                    this->sendToAllUsers(reply);
                    break;
                case 'k':
                    if (params.empty() && op == '+')
                    {
                        user->setSendCache(ERR_NEEDMOREPARAMS(name, "MODE", "please type a password (+k)"));
                       break;
                    }
                    if ((modes & KEY_PROTECTED) && op == '+')
                    {
                        user->setSendCache(ERR_KEYSET(user->nick_name.get(), name));
                       break;  
                    }
                    if (op == '+')
                    {
                        std::string pass = *params.begin();
                        params.pop_front();
                        if (pass.find_first_not_of("abcdefghijklmnopqrstuvwxyz01234A56789"))
                        {
							modes = (op == '+') ? modes | KEY_PROTECTED : modes & ~KEY_PROTECTED;
							password(pass);
                            reply = ":" + user->nick_name.get() + " MODE #" + this->name + " +k " + pass + "\r\n";
                            this->sendToAllUsers(reply);
                        }
                        else
                            user->setSendCache(ERR_KEYSET(user->nick_name.get(), name, "please type an alnum password"));
                    }
                    else
                    {	
                        modes = (op == '+') ? modes | KEY_PROTECTED : modes & ~KEY_PROTECTED;
                        reply = ":" + user->nick_name.get() + " MODE #" + this->name + " -k\r\n";
                        this->sendToAllUsers(reply);
                    }
                    break;
                case 'l' :
                    if (params.empty() && op == '+')
                    {
                        user->setSendCache(ERR_NEEDMOREPARAMS(name, "MODE", "please type user limit (+l)"));
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
							modes = (op == '+') ? modes | USER_LIMIT : modes & ~USER_LIMIT;
                            limit = _limit;
                            reply = ":" + user->nick_name.get() + " MODE #" + this->name + " +l " + s_limit + "\r\n";
                            this->sendToAllUsers(reply);
                        }
                        else 
                            user->setSendCache(ERR_NEEDMOREPARAMS(name, "MODE", "please type a numeric user limit (+l)"));
                    }
                    else
                    {
						modes = (op == '+') ? modes | USER_LIMIT : modes & ~USER_LIMIT;
                        reply = ":" + user->nick_name.get() + " MODE #" + this->name + " -l\r\n";
                        this->sendToAllUsers(reply);
                    }
                    break;
                case 'o':
                    if (params.empty())
                    {
                        user->setSendCache(ERR_NEEDMOREPARAMS(name, "MODE", "please type a nickname (o)"));
                        break;
                    }
					{
                        std::string	s_ChannelUser = params.front();
                        params.pop_front();                       
                        User * s_User = findUser(s_ChannelUser);
                        if (!s_User)
                            user->setSendCache(ERR_NOSUCHNICK(user->nick_name.get(), name, s_ChannelUser));
                        else
                        {
                           if (s_User == user)
                           {
                            break;
                           }
                                
                            if (op == '+')
                                _users_map.find(s_User)->second = OPERATOR;
                            else 
                                _users_map.find(s_User)->second = NONE;
                            
                            reply = ":" + user->nick_name.get() + " MODE #" + this->name + " " + op + "o " + s_ChannelUser + "\r\n";
                            this->sendToAllUsers(reply);
                        }
					}
                    break;
                
                default:
                    user->setSendCache(ERR_UNKNOWNMODE(user->nick_name.get(), name, c));
                    break;
            }
        
    }
    return true;
}

void	Wagner::cmd_mode(void)
{
	DEBUG_CALL_WAGNER
    
    std::string         reply;
    std::stringstream   ss_reply;
    ss_reply << request;
    reply = ":" + user->nick_name.get() + " " + ss_reply.str() + "\r\n";
    
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
        //channel->sendToAllUsers(reply);
    }

    // PUSH_TODO bool ProcessModeCmd
	//user->setSendCache(RPL_CHANNELMODEIS(user->nick_name.get(), channel));
	//user->setSendCache(RPL_NAMREPLY(user->nick_name.get(), channel));
	//user->setSendCache(RPL_ENDOFNAMES(user->nick_name.get(), channel));
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
