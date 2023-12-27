/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responses.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:39:48 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/27 18:08:39 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSES_HPP
# define RESPONSES_HPP

# include <sstream>

# include "User.hpp"
# include "Channel.hpp"
# include "MessageQueue.hpp"

# define HOSTNAME "localhost"
# define SERVERNAME "SuperServeur"
# define VERSION "1.0"
# define CREATION_DATE "2023/12/10"

class User;
class Channel;

// MODE
std::string	RPL_TRYAGAIN(std::string command, std::string info = "command not found");

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
std::string	PONG(std::string server);

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

std::string	RPL_NAMREPLY(std::string nickname, Channel *channel);
std::string	NICK(std::string old, std::string newnick);

//PING PONG
std::string	ERR_NOORIGIN();
std::string	ERR_NOORIGIN();
std::string	ERR_NOSUCHSERVER(std::string server);

std::string	ERR_NOTREGISTERED(void);

#endif
