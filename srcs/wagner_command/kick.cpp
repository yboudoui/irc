/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 06:36:01 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 12:32:48 by yboudoui         ###   ########.fr       */
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
	DEBUG_CALL_WAGNER_COMMAND
	if (!user->isConnected())
		return (user->send_message(ERR_NOTREGISTERED()));

	std::string	user_nick_name = user->nick_name;
	size_t		params_count = request->params.size();

	if (params_count < 2)
	{
		user->send_message(ERR_NEEDMOREPARAMS("", "KICK"));
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
		user->send_message(ERR_NOSUCHCHANNEL(user_nick_name, channelName));
		return ;
	}

    User * s_User = channel->findUser(user_nick_name);
	if (!s_User)
	{
		user->send_message(ERR_NOTONCHANNEL(user_nick_name, channel->name));
		return ;
	}


	if (!channel->isOperator(s_User))
	{
		user->send_message(ERR_CHANOPRIVSNEEDED(user_nick_name, channel->name));
		return ;
	}

    User * userToKick = channel->findUser(request->params[1]);
	if (!userToKick)
	{
		user->send_message(ERR_NOTONCHANNEL(user_nick_name, channel->name, request->params[1] + " is not on channel"));
		return ;
	}
	std::string	reason = "";
	if (params_count == 3)
	{
		reason = request->params[2];
	}
	std::string	reply = KICK(user_nick_name, channelName, userToKick->nick_name, reason);
	channel->sendToAllUsers(reply);
	channel->remove(userToKick);
}
