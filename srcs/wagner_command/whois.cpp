/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 06:37:27 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 11:24:25 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Wagner.hpp"

/*
4.5.2 Whois query
Command: WHOIS
Parameters: [<server>] <nickmask>[,<nickmask>[,...]]
This message is used to query information about particular user.

The server will answer this message with several numeric messages
indicating different statuses of each user which matches the nickmask
(if you are entitled to see them).  If no wildcard is present in the
<nickmask>, any information about that nick which you are allowed to
see is presented.  A comma (',') separated list of nicknames may be
given.
The latter version sends the query to a specific server.  It is
useful if you want to know how long the user in question has been
idle as only local server (ie. the server the user is directly
connected to) knows that information, while everything else is
globally known.

Numeric Replies:
ERR_NOSUCHSERVER
ERR_NONICKNAMEGIVEN
RPL_WHOISUSER
RPL_WHOISCHANNELS
RPL_WHOISCHANNELS
RPL_WHOISSERVER
RPL_AWAY
RPL_WHOISOPERATOR
RPL_WHOISIDLE
ERR_NOSUCHNICK
RPL_ENDOFWHOIS
*/

void	Wagner::cmd_whois(void)
{
	DEBUG_CALL_WAGNER_COMMAND
	/*
	std::string nickName = request->params[0];
	for (t_clients::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if ((*it)->is_alive() && *it != user)
		{
			if ((*it)->nick_name == nickName)
				return (user->send_message(RPL_WHOISUSER(user)));

		}
	}
	user->send_message(ERR_NOSUCHNICK(nickName));
	*/
}
