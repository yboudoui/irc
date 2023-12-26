/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner_join.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 09:22:49 by sethomas         ###   ########.fr       */
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
includes MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.  The
JOIN command needs to be broadcast to all servers so that each server
knows where to find the users who are on the channel.  This allows
optimal delivery of PRIVMSG/NOTICE messages to the channel.
If a JOIN is successful, the user is then sent the channel's topic
(using RPL_TOPIC) and the list of users who are on the channel (using
RPL_NAMREPLY), which must include the user joining.

Numeric Replies:
        ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
        ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
        ERR_CHANNELISFULL               ERR_BADCHANMASK
        ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
        RPL_TOPIC
*/

// TODO 
// /JOIN #channel password
// si un pass est saisi l'envoyer a join
void	Wagner::cmd_join(void)
{
	DEBUG_CALL_WAGNER

	if (request->params.empty())
		return (reply(Response::ERR_NEEDMOREPARAMS));

	std::vector< std::pair<std::string, available<std::string> > >	m;
	std::pair<std::string, available<std::string> >					new_pair;
	std::string														name;
	available<std::string>											password;
	size_t															index;

	for (index = 0; index < request->params.size(); index++)
	{
		name = request->params[index];
		if (name[0] != '#' && name[0] != '&')
			break ;
		new_pair.first = name.substr(1);
		m.push_back(new_pair);
	}

	for (size_t i = 0; i < m.size() && index < request->params.size(); i++)
		m[i].second(request->params[index++]);

/*	if (index < request.params.size())
		There is still some parameters.. error */

	for (size_t i = 0; i < m.size(); i++)
		_channel_map.find_or_create(m[i].first)->join(user, "usr_password");
}
