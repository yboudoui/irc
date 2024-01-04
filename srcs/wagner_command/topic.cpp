/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 06:37:11 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 09:13:43 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Wagner.hpp"

/*
Command: TOPIC
Parameters: <channel> [<topic>]

The TOPIC message is used to change or view the topic of a channel.
The topic for channel <channel> is returned if there is no <topic>
given.  If the <topic> parameter is present, the topic for that
channel will be changed, if the channel modes permit this action.
*/


void	Wagner::cmd_topic(void)
{
	DEBUG_CALL_WAGNER_COMMAND

	std::string	user_nick_name = user->nick_name;
	size_t		params_count = request->params.size();

//1. check si au moins 1 params
	if (params_count < 1)
	{
		user->send_message(ERR_NEEDMOREPARAMS("", "TOPIC"));
		return ;
	}

//2. prendre le param #1 - verifier que la channel existe
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

//3. verifier que user est sur la channel avec :
    User * s_User = channel->findUser(user->nick_name);
	if (!s_User)
	{
		user->send_message(ERR_NOTONCHANNEL(user_nick_name, channel->name));
		return ;
	}

//4. si il y a un parametre renvoyer le topic a l'utilisateur.
	if (params_count == 1)
	{
		if (channel->topic)
			user->send_message(RPL_TOPIC(user->nick_name, channel->name, channel->topic()));
		else
			user->send_message(RPL_NOTOPIC(user->nick_name, channel->name));
		return ;
	}
	else
	{
//5. si il y a deux parameter verifier si le topic n'est modificable que par les operateurs.
		if ((channel->modes & TOPIC_ONLY_OP) && !channel->isOperator(user))
		{
			user->send_message(ERR_CHANOPRIVSNEEDED(user_nick_name, channel->name));
			return ;
		}
		std::string newTopic = request->params[1];
		if (!newTopic.empty() && newTopic[0] == ':')
			newTopic = newTopic.substr(1);
		channel->topic(newTopic);
		
		std::string reply;
		reply = RPL_TOPIC(user->nick_name, channel->name, newTopic);
		channel->sendToAllUsers(reply);
	}
}
