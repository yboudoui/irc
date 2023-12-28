/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner_join.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/28 13:51:01 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "Wagner.hpp"
# include "vector"

/*
Comand: JOIN
Parameters: <channel>{,<channel>} [<key>{,<key>}]

The JOIN command is used by client to start listening a specific
channel. Whether or not a client is allowed to join a channel is
checked only by the server the client is connected to; all other
servers automatically add the user to the channel when it is received
from other servers.  The conditions which affect this are as follows:
	1.  the user must be invited if the channel is invite-only;
	2.  the user's nick/username/hostname must not match any active bans;
	3.  the correct key (password) must be given if it is set.

These are discussed in more detail under the MODE command (see
section 4.2.3 for more details).
Once a user has joined a channel, they receive notice about all
commands their server receives which affect the channel.  This
includes MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE. 
The
JOIN command needs to be broadcast to all servers so that each server
knows where to find the users who are on the channel.  This allows
optimal delivery of PRIVMSG/NOTICE messages to the channel.
If a JOIN is successful, the user is then sent the channel's topic
(using RPL_TOPIC) and the list of users who are on the channel (using
RPL_NAMREPLY), which must include the user joining.

Numeric Replies:

ERR_NEEDMOREPARAMS (461)
<command> :<reason>	

ERR_INVITEONLYCHAN (473) //canJoin
<channel> :<reason>
Returned when attempting to join a channel which is invite only without an invitation

ERR_BADCHANNELKEY (475) //canJoin
<channel> :<reason>
Returned when attempting to join a key-locked
channel either without a key or with the wrong key

ERR_CHANNELISFULL (471) // canJoin
<channel> :<reason>
Returned when attempting to join
a channel which is set +l and is already full



	ERR_NOSUCHCHANNEL (403)
	Used to indicate the given channel name is invalid, 
	or does not exist

	RPL_TOPIC

Erreurs non gerees
	ERR_TOOMANYCHANNELS (405)
	<channel> :<reason>
	Sent to a user when they have joined the maximum number
	of allowed channels and they tried to join another channel

	ERR_BADCHANMASK (476)
	<channel> :<reason>
	The given channel mask was invalid

	ERR_BANNEDFROMCHAN (474)
	<channel> :<reason>	
	Returned when attempting to join a channel a user is banned from
*/

// JOIN #chan1,#chan2,#chan3 password
void	Wagner::cmd_join(void)
{
	DEBUG_CALL_WAGNER
	if (!user->isConnected())
		return (user->setSendCache(ERR_NOTREGISTERED()));

	if (!user->isConnected())
		return (user->setSendCache(ERR_NOTREGISTERED()));
	//1. verifier qu'il y a au moins 1 param
	if (request->params.empty())
		return (user->setSendCache(ERR_NEEDMOREPARAMS("", "JOIN")));
    std::string channelsToJoin = *request->params.begin();
    request->params.pop_front();
	
	//1.2 recuperer le mot de pass si saisi
	std::string	userPassword = "";
	if (!request->params.empty())
    {
		userPassword = *request->params.begin();
		request->params.pop_front();
	}
	//2.	split le param1 sur les virgules
	//		(shlag >> ajout de la derniere , pour le split)
	channelsToJoin.append(",");
	unsigned long	pos = channelsToJoin.find(',');
	std::string		s_channel;
	bool hasJoin;
	while (pos != std::string::npos)
	{
		s_channel = channelsToJoin.substr(0, pos);
		channelsToJoin.erase(0, pos + 1);
		pos = channelsToJoin.find(',');

		if (!s_channel.empty() && s_channel[0] == '#')
			s_channel = s_channel.substr(1);
		//3. pour chaque channel (canJoin)
		hasJoin = find_or_create_channel(s_channel)->join(user, userPassword);
		if (hasJoin)
		{
			Channel * channel = find_channel(s_channel);
			user->join(channel);
			if (channel->topic)
				user->setSendCache(RPL_TOPIC(channel->name, channel->topic()));			
			user->setSendCache(RPL_WELCOME(user, channel->name, "Welcome ! You've join the channel "));
			user->setSendCache(RPL_CHANNELMODEIS(user->nick_name.get(), channel));
			user->setSendCache(RPL_NAMREPLY(user->nick_name.get(), channel));
			user->setSendCache(RPL_ENDOFNAMES(user->nick_name.get(), channel));
		}
	}
}
