/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner_quit.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/27 12:01:07 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "Wagner.hpp"

/*
Command: QUIT
Parameters: [<Quit message>]
A client session is ended with a quit message.  The server must close
the connection to a client which sends a QUIT message. If a "Quit
Message" is given, this will be sent instead of the default message,
the nickname.
When netsplits (disconnecting of two servers) occur, the quit message 
is composed of the names of two servers involved, separated by a
space.  The first name is that of the server which is still connected
and the second name is that of the server that has become
disconnected.
If, for some other reason, a client connection is closed without  the
client  issuing  a  QUIT  command  (e.g.  client  dies and EOF occurs
on socket), the server is required to fill in the quit  message  with
some sort  of  message  reflecting the nature of the event which
caused it to happen.

Numeric Replies: None.
*/

void	Wagner::cmd_quit(void)
{
	DEBUG_CALL_WAGNER
	// TODO : envoyer message d'info aux autres utilisateurs
	// TODO : supprimer le user de toutes les channels

	std::string	message = "default message quit";
	if (request->params.empty() == false)
	{
		message = request->params.back();
		request->params.pop_back();
	}

	user->is_alive(false);
}

