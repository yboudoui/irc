/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner_privmsg.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 09:19:54 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "Wagner.hpp"

/*
Command: PRIVMSG
Parameters: <receiver>{,<receiver>} <text to be sent>

PRIVMSG is used to send private messages between users.  <receiver>
is the nickname of the receiver of the message.  <receiver> can also
be a list of names or channels separated with commas.
The <receiver> parameter may also me a host mask  (#mask)  or  server
mask  ($mask).   In  both cases the server will only send the PRIVMSG
to those who have a server or host matching the mask.  The mask  must
have at  least  1  (one)  "."  in it and no wildcards following the
last ".".  This requirement exists to prevent people sending messages
to  "#*"  or "$*",  which  would  broadcast  to  all  users; from
experience, this is abused more than used responsibly and properly.
Wildcards are  the  '*' and  '?'   characters.   This  extension  to
the PRIVMSG command is only available to Operators.

Numeric Replies:

ERR_NORECIPIENT
ERR_NOTEXTTOSEND
ERR_CANNOTSENDTOCHAN
ERR_NOTOPLEVEL
ERR_WILDTOPLEVEL
ERR_TOOMANYTARGETS
ERR_NOSUCHNICK
RPL_AWAY
*/
void	Wagner::cmd_privmsg(void)
{
	DEBUG_CALL_WAGNER

	std::string	receiver, message = request->params.back();
	request->params.pop_back();

	reply.setMessage(message);
	while (!request->params.empty())
	{
		receiver = request->params.front().substr(1);
		request->params.pop_front();
		//_channel(user).send(Response::QUIT).toChannel(receiver);
		if (_channel_map.send(receiver, user, reply) == false)
			continue; // but still an error or message to someone
	}
}