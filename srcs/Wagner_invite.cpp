/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner_invite.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 08:54:12 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Wagner.hpp"

/*
Command: INVITE
Parameters: <nickname> <channel>

The INVITE message is used to invite users to a channel.  The
parameter <nickname> is the nickname of the person to be invited to
the target channel <channel>.  There is no requirement that the
channel the target user is being invited to must exist or be a valid
channel.  To invite a user to a channel which is invite only (MODE
+i), the client sending the invite must be recognised as being a
channel operator on the given channel.

*/
void	Wagner::cmd_invite(void)
{
	DEBUG_CALL_WAGNER

/*
1. check si au moins 2 params
user->setSendCache(ERR_NEEDMOREPARAMS("", "IVITE")));

2. prendre le param #1 - verifier que la channel existe
user->setSendCache(ERR_NOSUCHCHANNEL(user->getNickname(), <param#1>)));

3. verifier que user est sur la channel avec :
channel.isInChannel(user)
user->setSendCache(ERR_NOTONCHANNEL(user->getNickname(), <channelName>)));

4. verifier les droits operateurs de user avec :
channel.isOperator(user)
user->setSendCache(ERR_CHANOPRIVSNEEDED(user->getNickname(), <channelName>)));

5. verifier que la personne à invite est dans la base t_client avec
User* UserToInvite = findClient(nickToInvite);
user->setSendCache(ERR_NOSUCHNICK(<channelName>, nickToInvite)));

6. verifier si la personne à invite est deja dans le channel avec
User* UserToInvite = findUser(nickToInvite);
user->setSendCache(ERR_USERONCHANNEL(<channelName>, nickToInvite)));

7. si tout est OK :
	- ajouter le user à la channel 
	(je crois que c'est inutile de faire un vector d'invites )
user->setSendCache(RPL_INVITING(<nickToInvite>, channel)));


RPL_AWAY (301) ??? on ne gere pas le mode away
<nick> :<message>
Used in reply to a command directed at a user who is marked as away
*/

}

