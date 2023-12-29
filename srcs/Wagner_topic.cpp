/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner_topic.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/29 08:09:45 by sethomas         ###   ########.fr       */
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
	DEBUG_CALL_WAGNER

	std::string	user_nick_name = user->nick_name.get();
	size_t		params_count = request->params.size();

//1. check si au moins 1 params
	if (params_count < 1)
	{
		user->setSendCache(ERR_NEEDMOREPARAMS("", "TOPIC"));
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
		user->setSendCache(ERR_NOSUCHCHANNEL(user_nick_name, channelName));
		return ;
	}

//3. verifier que user est sur la channel avec :
    User * s_User = channel->findUser(user->nick_name.get());
	if (!s_User)
	{
		user->setSendCache(ERR_NOTONCHANNEL(user_nick_name, channel->name));
		return ;
	}

//4. si il y a un parametre renvoyer le topic a l'utilisateur.
	if (params_count == 1)
	{
		if (channel->topic)
			user->setSendCache(RPL_TOPIC(user->nick_name.get(), channel->name, channel->topic()));
		else
			user->setSendCache(RPL_NOTOPIC(user->nick_name.get(), channel->name));
		return ;
	}else{
		
	//5. si il y a deux parameter verifier si le topic n'est modificable que par les operateurs.
		if ((channel->modes & TOPIC_ONLY_OP) && !channel->isOperator(user))
		{
			user->setSendCache(ERR_CHANOPRIVSNEEDED(user_nick_name, channel->name));
			return ;
		}
		std::string newTopic = request->params[1];
		if (!newTopic.empty() && newTopic[0] == ':')
			newTopic = newTopic.substr(1);
		channel->topic(newTopic);
		
		
		user->sendTo(channel, RPL_TOPIC(user->nick_name.get(), channel->name, newTopic));
	}
}
