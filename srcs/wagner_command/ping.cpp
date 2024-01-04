/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 06:36:38 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 08:18:01 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Wagner.hpp"

/*
Ping message

Command: PING
Parameters: <server1> [<server2>]

The PING message is used to test the presence of an active client at
the other end of the connection.  A PING message is sent at regular
intervals if no other activity detected coming from a connection.  If
a connection fails to respond to a PING command within a set amount
of time, that connection is closed

Any client which receives a PING message must respond to <server1>
(server which sent the PING message out) as quickly as possible with
an appropriate PONG message to indicate it is still there and alive.
Servers should not respond to PING commands but rely on PINGs from
the other end of the connection to indicate the connection is alive.
If the <server2> parameter is specified, the PING message gets
forwarded there.

   Numeric Replies:

           ERR_NOORIGIN                    ERR_NOSUCHSERVER

   Examples:

   PING tolsun.oulu.fi             ; server sending a PING message to
                                   another server to indicate it is still
                                   alive.

   PING WiZ                        ; PING message being sent to nick WiZ

4.6.3 Pong message

      Command: PONG
   Parameters: <daemon> [<daemon2>]

   PONG message is a reply to ping message.  If parameter <daemon2> is
   given this message must be forwarded to given daemon.  The <daemon>
   parameter is the name of the daemon who has responded to PING message
   and generated this message.

   Numeric Replies:

           ERR_NOORIGIN                    ERR_NOSUCHSERVER
*/

void	Wagner::cmd_ping(void)
{
	DEBUG_CALL_WAGNER_COMMAND
	if (!request->params.size())
		user->send_message(ERR_NOORIGIN());
	std::string server;
	while (request->params.size())
	{
		server = *request->params.begin();
		request->params.pop_front();
		if (server != HOSTNAME)
			user->send_message(ERR_NOSUCHSERVER(server));
		else
			user->send_message(PONG(server));
	}
}
