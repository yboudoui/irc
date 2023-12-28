/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner_kick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/28 17:04:30 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "Wagner.hpp"

/*
Command: KICK
Parameters: <channel> <user> [<comment>]
KICK #channel userToKick :je ne veux plus de toi dans ce channel
*/

/*
TODO check this note
NOTE:
Il est possible d'étendre les paramètres de la commande KICK ainsi :
<canal>{,<canal>} <utilisateur>{,<utilisateur>} [<commentaire>] 
*/
void	Wagner::cmd_kick(void)
{
	DEBUG_CALL_WAGNER
	if (!user->isConnected())
		return (user->setSendCache(ERR_NOTREGISTERED()));

	std::string	user_nick_name = user->nick_name.get();
	size_t		params_count = request->params.size();

	if (params_count < 2)
	{
		user->setSendCache(ERR_NEEDMOREPARAMS("", "KICK"));
		return ;
	}
	std::string channelName = request->params[0];
    if (!channelName.empty() && channelName[0] == '#')
	{
		channelName = channelName.substr(1);
	}
	Channel*	channel = find_channel(channelName);
	if (channel == NULL)
	{
		user->setSendCache(ERR_NOSUCHCHANNEL(user_nick_name, channelName));
		return ;
	}

	available<t_client>	current_client = channel->find_by(*user);
	if (current_client == false)
	{
		user->setSendCache(ERR_NOTONCHANNEL(user_nick_name, channel->name));
		return ;
	}

	if ((current_client().second & INVITED) == false)
	{
		user->setSendCache(ERR_CHANOPRIVSNEEDED(user_nick_name, channel->name));
		return ;
	}

	available<t_client>	client = channel->find_by(nickName(request->params[1]));
	if (client == false)
	{
		user->setSendCache(ERR_NOTONCHANNEL(user_nick_name, channel->name));
		return ;
	}

	std::string	reply;
	reply << *request;
	client().first->setSendCache(reply);
	channel->remove(client().first);
	channel->sendToAllUsers(reply);
}
