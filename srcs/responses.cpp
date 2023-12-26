/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responses.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:36:16 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 18:11:25 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"


std::string	ERR_NEEDMOREPARAMS(std::string channel, std::string cmd, std::string reason)
{
	std::stringstream	output;

	(void)channel;
	output << ":" << HOSTNAME;
	output << " 461";
	if (channel.size())
		output << " #" << channel;
	output << " " << cmd;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*
RPL_TRYAGAIN (263)
<command> :<info>
When a server drops a command without processing it, 
it MUST use this reply.
*/
std::string	RPL_TRYAGAIN(std::string command, std::string info)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " " << command;
	output << " :" << info;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*** CONNECT ****/
/*
RPL_WELCOME (001)
:Welcome to the Internet Relay Network <nick>!<user>@<host>
*/
std::string	RPL_WELCOME(User * user)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 001 ";
	output << user->nick_name.get();
	output << " :Welcome to the Internet Relay Network ";
	output << user->nick_name.get() << "!" << user->user_name.get();
	output << "@"+ user->host_name.get();
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*
RPL_YOURHOST (002)
:Your host is <servername>, running version <version>
*/
std::string	RPL_YOURHOST()
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 002 ";
	output << ": Your host is <servername>, running version <version>";
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*
RPL_CREATED (003)
:This server was created <date>
*/
std::string	RPL_CREATED()
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 003 ";
	output << ": This server was created <date>";
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*
RPL_MYINFO (004)
:<server_name> <version> <user_modes> <chan_modes>
*/
std::string	RPL_MYINFO()
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 004 ";
	output << ": <server_name> <version> <user_modes> <chan_modes>";
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
/*
RPL_BOUNCE (005)
Also known as RPL_PROTOCTL (Bahamut, Unreal, Ultimate)
std::string	RPL_BOUNCE()
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 005";
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
*/


/*** CHANNEL MODES ***/

/*
ERR_NICKCOLLISION (436) // IDEM 433 ?
<nick> :<reason>
Returned by a server to a client when it detects a nickname collision
*/

/*
ERR_NOTOPLEVEL (413) ??? ON NE GERE PAS LES MASQUES ?
<mask> :<reason>
Used when a message is being sent 
to a mask without being limited to a top-level 
domain (i.e. * instead of *.au)
*/

/*
ERR_WILDTOPLEVEL (414)
<mask> :<reason>
Used when a message is being sent
to a mask with a wild-card for a top level domain (i.e. *.*)
*/

