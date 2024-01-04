/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 06:37:02 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 12:33:24 by yboudoui         ###   ########.fr       */
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
mask  ($mask).

In  both cases the server will only send the PRIVMSG
to those who have a server or host matching the mask.  The mask  must
have at  least  1  (one)  "."  in it and no wildcards following the
last ".".  This requirement exists to prevent people sending messages
to  "#*"  or "$*",  which  would  broadcast  to  all  users; from
experience, this is abused more than used responsibly and properly.
Wildcards are  the  '*' and  '?'   characters.   This  extension  to
the PRIVMSG command is only available to Operators.
RPL_AWAY (301) // qq comandes non gerees // idem mask
<nick> :<message>
*/
void	Wagner::cmd_privmsg(void)
{
	DEBUG_CALL_WAGNER_COMMAND
	if (!user->isConnected())
		return (user->send_message(ERR_NOTREGISTERED()));
	std::string	s_target, message, response, senderNickname;

	// 1. verifier qu'il y a un destinataire
	if (!request->params.size())
		return(user->send_message(ERR_NORECIPIENT()));
    s_target = *request->params.begin();
    request->params.pop_front();

	// 2. verifier qu'il y a un message a envoyer
	if (!request->params.size())
		return(user->send_message(ERR_NOTEXTTOSEND()));
	message = *request->params.begin();
	request->params.pop_front();
	// supprime le : si necessaire du message
	if (!message.empty() && message[0] == ':')
		message = message.substr(1);

	// supprime le # si necessaire de la cible
	if (!s_target.empty() && s_target[0] == '#')
		s_target = s_target.substr(1);

	// 3. verifier qu'il n'y a pas d'ambiguite (channel.name et user.nickname)
	Channel*	target_channel = find_channel(s_target);
	User*		target_user = findClient(s_target);

	if (target_channel && target_user)
		return(user->send_message(ERR_TOOMANYTARGETS(s_target)));

	response = PRIVMSG(user->nick_name, s_target, message);
	if (target_channel)
	{
		// 4. verifier que user appartient au channel
		if (target_channel->isInChannel(user))
			return(target_channel->send(user->nick_name, response));
		else
			return(user->send_message(ERR_CANNOTSENDTOCHAN(s_target)));
	}
	else if (target_user)
		return(target_user->send_message(response));
	return(user->send_message(ERR_NOSUCHNICK(user->nick_name, "", s_target)));
}
