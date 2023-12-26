/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responses.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:36:16 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 16:16:43 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

Response::Response(void)
{
	_pfonc_map[5]	= &Response::__263;
	_pfonc_map[7]	= &Response::_ERR_NONICKNAMEGIVEN;
	_pfonc_map[8]	= &Response::_ERR_ERRONEUSNICKNAME;
	_pfonc_map[9]	= &Response::_ERR_NICKNAMEINUSE;
	_pfonc_map[10]	= &Response::_ERR_NEEDMOREPARAMS;
	_pfonc_map[14]	= &Response::_QUIT;

}

void	Response::setHostName(std::string hostName)
{
	_hostname = hostName;
}

void	Response::setUser(User* user)
{
	// TODO check NULL
	_user = user;
}

void	Response::setRequest(Message* message)
{
	// TODO check NULL
	_request = message;
}

void	Response::setChannel(Channel* channel)
{
	_channel = channel;
}

void	Response::setMessage(std::string message)
{
	_message = message;
}

void	Response::operator () (int code, bool kill)
{
	if (_user->is_alive() == false)
		return ;
	MessageQueue	queue;

	for (size_t i = 0; i < MAX_REPONSE_CODE; i++)
	{
		if ((1u << i) & code)
			queue += new Message((this->*(_pfonc_map[i]))());
	}
	_user->setSendCache(queue.str());
	_user->is_alive(!kill);
}

std::string	Response::__263(void)
{
	std::stringstream	output;

	output << ":" << _hostname;
	output << " 263 ";
	output << _request->command.name;
	output << ": Unknown command: " << _request->command.name;
	return (output.str());
}

std::string	Response::_ERR_NONICKNAMEGIVEN(void)
{
	std::stringstream	output;

	output << ":" << _hostname;
	output << " 431 ";
	output << ": a nickname parameter is expected";
	return (output.str());
}

std::string	Response::_ERR_ERRONEUSNICKNAME(void)
{
	std::stringstream	output;

	output << ":" << _hostname;
	output << " 432 ";
	output << _user->nick_name.get();
	output << " : a nickname parameter is expected";
	return (output.str());
}

std::string	Response::_ERR_NICKNAMEINUSE(void)
{
	std::stringstream	output;

	output << ":" << _hostname;
	output << " 433 ";
	output << _user->nick_name.get();
	output << " :nickname already in use";
	return (output.str());
}

std::string	Response::_ERR_NEEDMOREPARAMS(void)
{
	std::stringstream	output;

	output << ":" << _hostname;
	output << " 461";
	output << " " << _request->command.name << " : command requires more parameters";
	return (output.str());
}

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
ERR_NOSUCHCHANNEL (403)
<channel> :<reason> 
Used to indicate the given channel name is invalid, or does not exist
*/
std::string	ERR_NOSUCHCHANNEL(std::string nickname, std::string channel, std::string reason)
{
	std::stringstream	output;

	(void)reason;
	output << ":" << HOSTNAME;
	output << " 403 ";
	output << " " << nickname;
	output << " " << channel;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*
ERR_UMODEUNKNOWNFLAG (501)
:<reason> 
Returned by the server to indicate that a MODE 
message was sent with a nickname parameter 
and that the mode flag sent was not recognised
*/
std::string	ERR_UMODEUNKNOWNFLAG(std::string nickname, std::string reason)
{
	std::stringstream	output;

	(void)reason;
	output << ":" << HOSTNAME;
	output << " 501";
	output << " " << nickname;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*
ERR_CHANOPRIVSNEEDED : 
Returned by any command requiring special channel 
privileges (eg. channel operator) to indicate 
the operation was unsuccessfull
*/
std::string	ERR_CHANOPRIVSNEEDED(std::string nickname, std::string channel, std::string reason)
{
	std::stringstream	output;

	(void)reason;
	output << ":" << HOSTNAME;
	output << " 482 #" << channel;
	output << " " << nickname;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/* 
ERR_NOTONCHANNEL (442) 
<channel> :<reason>   Returned by the server 
whenever a client tries to perform a channel 
effecting command for which the client is not a member
*/
std::string	ERR_NOTONCHANNEL(std::string nickname, std::string channel, std::string reason)
{
	std::stringstream	output;

	(void)reason;
	output << ":" << HOSTNAME;
	output << " 442 #" << channel;
	output << " " << nickname;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*
ERR_KEYSET (467)
<channel> :<reason>
Returned when the channel key for a 
channel has already been set 
*/
std::string	ERR_KEYSET(std::string nickname, std::string channel, std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 467 #" << channel;
	output << " " << nickname;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*
RPL_CHANNELMODEIS (324)
<channel> <mode> <mode_params>
*/
std::string	RPL_CHANNELMODEIS(std::string nickname, Channel* channel)
{
	std::stringstream	output;
	(void)nickname;
	output << ":" << HOSTNAME;
	output << " 324";
	output << " " << nickname;
	output << " #" << channel->name.get();
	output << " " << channel->getChannelModes();
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*
ERR_NOSUCHNICK (401)
<nick> :<reason> 
Used to indicate the nickname parameter supplied 
to a command is currently unused 
*/
std::string	ERR_NOSUCHNICK(std::string channel, std::string nickname, std::string reason)
{
	std::stringstream	output;
	(void)nickname;
	output << ":" << HOSTNAME;
	output << " 401";
	if (channel.size())
		output << " #" << channel;
	output << " " << nickname;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*
ERR_UNKNOWNMODE (472)
<char> :<reason>
Returned when a given mode is unknown 
*/
std::string	ERR_UNKNOWNMODE(std::string channel, char c, std::string reason)
{
	std::stringstream	output;
	output << ":" << HOSTNAME;
	output << " 472";
	output << " #" << channel;
	output << " " << c;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}


/*
ERR_NONICKNAMEGIVEN (431)
:<reason>
Returned when a nickname parameter expected for a command isn't found
*/
std::string	ERR_NONICKNAMEGIVEN(std::string reason)
{
	std::stringstream	output;
	output << ":" << HOSTNAME;
	output << " 431";
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
/*
ERR_NICKNAMEINUSE (433)
<nick> :<reason>
Returned by the NICK command when the given nickname is already in use
*/
/*
ERR_NICKCOLLISION (436) // IDEM 433 ?
<nick> :<reason>
Returned by a server to a client when it detects a nickname collision
*/
std::string	ERR_NICKNAMEINUSE(std::string nick, std::string reason)
{
	std::stringstream	output;
	output << ":" << HOSTNAME;
	output << " 433";
	output << " " << nick;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
/*
ERR_ERRONEUSNICKNAME (432)
<nick> :<reason>
Returned after receiving a NICK message which contains a nickname
which is considered invalid, such as it's reserved ('anonymous')
or contains characters considered invalid for nicknames.
*/
std::string	ERR_ERRONEUSNICKNAME(std::string nick, std::string reason)
{
	std::stringstream	output;
	output << ":" << HOSTNAME;
	output << " 432";
	output << " " << nick;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}


/*
ERR_ALREADYREGISTERED (462)
:<reason>
Returned by the server to any link which attempts to register again
*/
std::string	ERR_ALREADYREGISTRED(std::string nick, std::string reason)
{
	std::stringstream	output;
	output << ":" << HOSTNAME;
	output << " 462";
	output << " " << nick;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
/*
ERR_PASSWDMISMATCH (464)
:<reason>
Returned by the PASS command to indicate the given password
was required and was either not given or was incorrect
*/
std::string	ERR_PASSWDMISMATCH(std::string nick, std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 464";
	output << " " << nick;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*** INVITE ***/
/*
ERR_USERONCHANNEL (443)
<nick> <channel> [:<reason>]
Returned when a client tries to 
invite a user to a channel they're already on
*/
std::string	ERR_USERONCHANNEL(std::string nick, std::string channel, std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 443";
	output << " " << nick;
	output << " " << channel;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*
341	RPL_INVITING (341)
<nick> <channel>	
Returned by the server to indicate that the attempted INVITE
message was successful and is being passed onto the end client.
Note that RFC1459 documents the parameters in the reverse order. 
the format given here is the format used on production servers, 
and should be considered the standard reply above that given by RFC1459.
*/
std::string	RPL_INVITING(std::string nick, std::string channel)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 341";
	output << " " << nick;
	output << " " << channel;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*** TOPIC */
/*
RPL_NOTOPIC (331)
<channel> :<info>
Response to TOPIC when no topic is set
*/
std::string	RPL_NOTOPIC(std::string channel, std::string info)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 331";
	output << " " << channel;
	output << " :" << info;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*
RPL_TOPIC (332)
<channel> :<info>
Response to TOPIC when no topic is set
*/
std::string	RPL_TOPIC(std::string channel, std::string topic)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 332";
	output << " " << channel;
	output << " :" << topic;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

std::string	PONG()
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " PONG ";
	output << HOSTNAME;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

std::string	RPL_WHOISUSER(User * _user)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 311 ";
	output << _user->nick_name.get() << " ";
	output << _user->nick_name.get() << " ";
	output << _user->user_name.get() << " ";
	output << _user->host_name.get() << " ";
	output << _user->real_name.get() << " ";
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*
PRIVMSG
*/
std::string	PRIVMSG(std::string sender, std::string channel, std::string message)
{
	std::stringstream	output;

	output << ":" <<  sender;
	output << " PRIVMSG ";
	output << "#" << channel;
	output << " :" << message;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*
ERR_NORECIPIENT (411)
:<reason>
Returned when no recipient is given with a command
*/
std::string	ERR_NORECIPIENT(std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 411";
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*
ERR_NOTEXTTOSEND (412)
:<reason>
Returned when NOTICE/PRIVMSG is used with no message given
*/
std::string	ERR_NOTEXTTOSEND(std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 412";
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*
ERR_CANNOTSENDTOCHAN (404)
<channel> :<reason>	
Sent to a user who does not have the rights
to send a message to a channel
*/
std::string	ERR_CANNOTSENDTOCHAN(std::string channel, std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 404";
	output << " " << channel;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
/*
ERR_TOOMANYTARGETS (407)
<target> :<reason> 
The given target(s) for a
command are ambiguous in that they relate to too many targets
*/
std::string	ERR_TOOMANYTARGETS(std::string target, std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 407";
	output << " " << target;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*
ERR_NOTOPLEVEL (413) ??? ON NE GERE PAS LES MASQUES ?
<mask> :<reason>
Used when a message is being sent 
to a mask without being limited to a top-level 
domain (i.e. * instead of *.au)

ERR_WILDTOPLEVEL (414)
<mask> :<reason>
Used when a message is being sent
to a mask with a wild-card for a top level domain (i.e. *.*)
*/



// JOIN
/*
ERR_INVITEONLYCHAN (473) //canJoin
<channel> :<reason>
Returned when attempting to join a channel which is invite only without an invitation
*/
std::string	ERR_INVITEONLYCHAN(std::string channel, std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 473";
	output << " " << channel;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
/*
ERR_BADCHANNELKEY (475) //canJoin
<channel> :<reason>
Returned when attempting to join a key-locked
channel either without a key or with the wrong key
*/
std::string	ERR_BADCHANNELKEY(std::string channel, std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 475";
	output << " " << channel;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*
ERR_CHANNELISFULL (471) // canJoin
<channel> :<reason>
Returned when attempting to join
a channel which is set +l and is already full
*/
std::string	ERR_CHANNELISFULL(std::string channel, std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 471";
	output << " " << channel;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
/*
ERR_BANNEDFROMCHAN (474) // canJoin
<channel> :<reason>
*/
std::string	ERR_BANNEDFROMCHAN(std::string channel, std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 474";
	output << " " << channel;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

/*
RPL_NAMREPLY (474)
:<server> 353 <nickname> <channel> :[[@|+]<nick>] [@[|+]<nick>] ...
<channel> :<reason>
*/
std::string	RPL_NAMREPLY(std::string nickname, Channel *channel)
{
	std::stringstream	output;
	(void)nickname;
	output << ":" << HOSTNAME;
	output << " 353";
	output << " " << nickname;
	output << " #" << channel->name.get();
	output << " :" << channel->getUserList();
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

std::string	Response::_QUIT(void)
{
	std::stringstream	output;

	output << " QUIT " << _message;
	return (output.str());
}
