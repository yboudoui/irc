/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner_kick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 21:25:58 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "Wagner.hpp"

/*
Command: KICK
Parameters: <channel> <user> [<comment>]
KICK #channel userToKick :je ne veux plus de toi dans ce channel
*/

void	Wagner::cmd_kick(void)
{
	DEBUG_CALL_WAGNER
/*
1. check si au moins 2 params
user->setSendCache(ERR_NEEDMOREPARAMS("", "KICK")));

2. prendre le param #1 - verifier que la channel existe
user->setSendCache(ERR_NOSUCHCHANNEL(user->getNickname(), <param#1>)));

3. verifier que user est sur la channel avec :
channel.isInChannel(user)
user->setSendCache(ERR_NOTONCHANNEL(user->getNickname(), <channelName>)));

4. verifier les droits operateurs de user avec :
channel.isOperator(user)
user->setSendCache(ERR_CHANOPRIVSNEEDED(user->getNickname(), <channelName>)));

5. verifier que la personne à kick est dans le channel avec
User* UserToKick = channel.findUser(nickToKick);
user->setSendCache(ERR_NOTONCHANNEL(user->getNickname(), <channelName>)));

6. si tout est OK :
	- envoyer un message au UserToKick (avec le parameter si il y en a un)
	- le supprimer de la channel...

ERR_BADCHANMASK (476) ??? ce message semble ne pas nous concerner ?
<channel> :<reason>	
The given channel mask was invalid
*/
}
