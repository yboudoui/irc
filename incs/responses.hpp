/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responses.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:39:48 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 16:46:41 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSES_HPP
# define RESPONSES_HPP

# include <sstream>

# include "User.hpp"
# include "Channel.hpp"
# include "MessageQueue.hpp"
# define HOSTNAME "localhost"

class User;
class Channel;

// MODE

std::string	RPL_WELCOME(User * user);
std::string	RPL_YOURHOST();
std::string	RPL_CREATED();
std::string	RPL_MYINFO();

std::string	ERR_NEEDMOREPARAMS(std::string channel, std::string cmd, std::string reason = "command requires more parameters");
std::string	ERR_NOSUCHCHANNEL(std::string nickname, std::string channel, std::string reason = "no such channel");
std::string	ERR_UMODEUNKNOWNFLAG(std::string nickname, std::string reason = "U MODE UNKNOWN FLAG");
std::string	ERR_CHANOPRIVSNEEDED(std::string nickname, std::string channel, std::string reason = "Channel operator privilege needed");
std::string	ERR_NOTONCHANNEL(std::string nickname, std::string channel, std::string reason = "You are not a member");
std::string	ERR_KEYSET(std::string nickname, std::string channel, std::string reason = "the channel key has already been set ");
std::string	ERR_NOSUCHNICK(std::string channel, std::string nickname, std::string reason = "the nickname parameter supplied is unused");
std::string	ERR_UNKNOWNMODE(std::string channel, char c, std::string reason = "the given mode in unknown");

std::string	RPL_CHANNELMODEIS(std::string nickname, Channel* channel);

// NICK
std::string	ERR_NONICKNAMEGIVEN(std::string reason = "a nickname parameter is expected");
std::string	ERR_NICKNAMEINUSE(std::string nick, std::string reason = "the given nickname is already in use");
std::string	ERR_ERRONEUSNICKNAME(std::string nick, std::string reason = "the given nickname is considered invalid");

//PASS 
std::string	ERR_ALREADYREGISTRED(std::string nick, std::string reason = "You are already registered");
std::string	ERR_PASSWDMISMATCH(std::string nick, std::string reason = "A Password is requiered");

// INVITE
std::string	ERR_USERONCHANNEL(std::string nick, std::string channel, std::string reason = "user is already on the channel");
std::string	RPL_INVITING(std::string nick, std::string channel);


// TOPIC
std::string	RPL_NOTOPIC(std::string channel, std::string info = "no topic is set");
std::string	RPL_TOPIC(std::string channel, std::string topic);

// PING
std::string	PONG();

// WHOIS
std::string	RPL_WHOISUSER(User * _user);

// PRIVMSG
std::string	PRIVMSG(std::string sender, std::string channel, std::string message);
std::string	ERR_NORECIPIENT(std::string reason = "no recipient is given with the command");
std::string	ERR_NOTEXTTOSEND(std::string reason = "no message given");
std::string	ERR_CANNOTSENDTOCHAN(std::string channel, std::string reason = "no rights to send text to the channel");
std::string	ERR_TOOMANYTARGETS(std::string target, std::string reason = "the given target is ambigous");
//std::string	ERR_NOSUCHNICK(std::string nick, std::string reason = "the nickname parameter supplied to the command is currently unused");

// JOIN
std::string	ERR_INVITEONLYCHAN(std::string channel, std::string reason = "invite only channel");
std::string	ERR_BADCHANNELKEY(std::string channel, std::string reason = "bad channel key");
std::string	ERR_CHANNELISFULL(std::string channel, std::string reason = "channel is full");
std::string	ERR_BANNEDFROMCHAN(std::string channel, std::string reason = "banned ... #sorry");


class Response
{
	public:
		Response(void);
		typedef enum e_reponse_code {
			NONE_REPONSE_CODE,
			_001					= (1UL << 0),
			_002					= (1UL << 1),
			_003					= (1UL << 2),
			_004					= (1UL << 3),
			_005					= (1UL << 4),
			_263					= (1UL << 5),
			RPL_WHOISUSER			= (1UL << 6),
			ERR_NONICKNAMEGIVEN		= (1UL << 7),
			ERR_ERRONEUSNICKNAME	= (1UL << 8),
			ERR_NICKNAMEINUSE		= (1UL << 9),
			ERR_NEEDMOREPARAMS		= (1UL << 10),
			ERR_PASSWDMISMATCH		= (1UL << 11),
			PONG					= (1UL << 12),
			PRIVMSG					= (1UL << 13),
			QUIT					= (1UL << 14),
			MAX_REPONSE_CODE		= 15,
		}	t_reponse_code;
		void			setHostName(std::string hostName);
		void			setUser(User* user);
		void			setRequest(Message* message);
		void			setChannel(Channel* channel);
		void			setMessage(std::string message);

		void	operator () (int code, bool kill = false);

	private:
		typedef std::string (Response::*pfonc)(void);
		pfonc		_pfonc_map[MAX_REPONSE_CODE + 1];
		std::string	_hostname;
		User		*_user;
		Message		*_request;
		Channel		*_channel;
		std::string _message;

		std::string	__001(void);
		std::string	__002(void);
		std::string	__003(void);
		std::string	__004(void);
		std::string	__005(void);

/*	RPL_TRYAGAIN (263) <command> :<info>
	When a server drops a command without processing it,it MUST use this reply.
*/		std::string	__263(void);

/*	ERR_NONICKNAMEGIVEN (431) :<reason>
	Returned when a nickname parameter expected for a command isn't found
*/		std::string	_ERR_NONICKNAMEGIVEN(void);

/*	ERR_ERRONEUSNICKNAME (432) <nick> :<reason> 
	Returned after receiving a NICK message which contains a nickname which is considered invalid 
	such as it's reserved ('anonymous') or contains characters considered invalid for nicknames.
*/		std::string	_ERR_ERRONEUSNICKNAME(void);

/*	ERR_NICKNAMEINUSE (433) <nick> :<reason> 
	Returned after receiving a NICK message which contains a nickname which is considered invalid 
	such as it's reserved ('anonymous') or contains characters considered invalid for nicknames.
*/		std::string	_ERR_NICKNAMEINUSE(void);

/*	ERR_NEEDMOREPARAMS (461) <command> :<reason> ""
	Returned by the server by any command which requires more parameters than the number of parameters given
*/		std::string	_ERR_NEEDMOREPARAMS(void);

/*	ERR_PASSWDMISMATCH (464) :<reason>
	Returned by the PASS command to indicate the given password was required and was either not given 
	or was incorrect
*/		std::string	_464_ERR_PASSWDMISMATCH(void);

		std::string	_PONG(void);
		std::string	_RPL_WHOISUSER(void);
		std::string	_PRIVMSG(void);
		std::string	_QUIT(void);
};

#endif
