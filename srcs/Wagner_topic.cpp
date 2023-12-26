/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner_topic.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 10:58:32 by sethomas         ###   ########.fr       */
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
/*
1. check si au moins 2 params
user->setSendCache(ERR_NEEDMOREPARAMS("", "INVITE")));

2. prendre le param #1 - verifier que la channel existe
user->setSendCache(ERR_NOSUCHCHANNEL(user->getNickname(), <param#1>)));

3. verifier que user est sur la channel avec :
channel.isInChannel(user)
user->setSendCache(ERR_NOTONCHANNEL(user->getNickname(), <channelName>)));

4. si il y a un param <topic>
	verifier si le topic n'est modificable que par les op avec.
	if (channel.getMode(TOPIC_ONLY_OP))
	{
		if  (channel.isOperator(user))
			channel.setTopic(<topic>)
		else
			user->setSendCache(ERR_CHANOPRIVSNEEDED(user->getNickname(), <channelName>)));
	}
	else
		channel.setTopic(<topic>)

5. Envoyer :  
	if (channel.getTopic().size())
		RPL_TOPIC(channel.getName(), channel.getTopic());
	else
		RPL_NOTOPIC(channel.getName());
*/
}
