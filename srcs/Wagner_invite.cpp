/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner_invite.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/27 17:29:34 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Wagner.hpp"

/*
Command: INVITE
Parameters: <nickname> <channel>

The INVITE message is used to invite users to a channel.  The
parameter <nickname> is the nickname of the person to be invited to
the target channel <channel>.  There is no requirement that the
channel the target user is being invited to must exist or be a valid
channel.  To invite a user to a channel which is invite only (MODE
+i), the client sending the invite must be recognised as being a
channel operator on the given channel.

*/
void	Wagner::cmd_invite(void)
{
	DEBUG_CALL_WAGNER
	if (!user->isConnected())
		return (user->setSendCache(ERR_NOTREGISTERED()));

	std::string	channelName;
	std::string	nickToInvite;
	std::string	userNickName = user->nick_name.get();
	size_t		paramsCount = request->params.size();

//1. check si au moins 2 params
	if (paramsCount < 2)
	{
		user->setSendCache(ERR_NEEDMOREPARAMS("", "IVITE"));
		return ;
	}

	nickToInvite = request->params[0];
	channelName = request->params[1];
	Channel	*channel = find_channel(channelName);

//2. prendre le param #1 - verifier que la channel existe
	if (channel == NULL)
	{
		user->setSendCache(ERR_NOSUCHCHANNEL(userNickName, channelName));
		return ;
	}

//3. verifier que user est sur la channel avec :
	available<t_client>	current_client = channel->find_by(*user);
	if (current_client == false)
	{
		user->setSendCache(ERR_NOTONCHANNEL(userNickName, channelName));
		return ;
	}

//4. verifier les droits operateurs de user avec :
	if ((current_client().second & OPERATOR) == false)
	{
		user->setSendCache(ERR_CHANOPRIVSNEEDED(userNickName, channelName));
		return ;
	}

//5. verifier que la personne à invite est dans la base t_client avec
	available<t_client>	client = channel->find_by(nickName(nickToInvite));
	if (client == false)
	{
		user->setSendCache(ERR_NOSUCHNICK(channelName, nickToInvite));
		return ;
	}

//6. verifier si la personne à invite est deja dans le channel avec
	if ((client().second & INVITED) == false)
	{
		user->setSendCache(ERR_USERONCHANNEL(channelName, nickToInvite));
		return ;
	}

//	channel->invite(client.first);
	user->setSendCache(RPL_INVITING(nickToInvite, channelName));
}

