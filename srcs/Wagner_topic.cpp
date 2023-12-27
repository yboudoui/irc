/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner_topic.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/27 15:36:43 by sethomas         ###   ########.fr       */
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

	std::string	channel_name;
	std::string	user_nick_name = user->nick_name.get();
	size_t		params_count = request->params.size();

//1. check si au moins 2 params
	if (params_count < 2)
	{
		user->setSendCache(ERR_NEEDMOREPARAMS("", "TOPIC"));
		return ;
	}

//2. prendre le param #1 - verifier que la channel existe
	Channel*	channel = find_channel(request->params[0]);
	if (channel == NULL)
	{
		user->setSendCache(ERR_NOSUCHCHANNEL(user_nick_name, request->params[0]));
		return ;
	}


//3. verifier que user est sur la channel avec :
	available<t_client>	current_client = channel->find_by(*user);
	if (current_client == false)
	{
		user->setSendCache(ERR_NOTONCHANNEL(user_nick_name, channel_name));
		return ;
	}

/*
//4. si il y a un param <topic> verifier si le topic n'est modificable que par les op avec.
	if (channel.getMode(TOPIC_ONLY_OP))
	{
		if  (channel.isOperator(user))
			channel.setTopic(<topic>)
		else
			user->setSendCache(ERR_CHANOPRIVSNEEDED(user->getNickname(), <channelName>)));
	}
	else
		channel.setTopic(<topic>)

//5. Envoyer :
	if (channel.getTopic().size())
		RPL_TOPIC(channel.getName(), channel.getTopic());
	else
		RPL_NOTOPIC(channel.getName());
*/
}
