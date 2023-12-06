/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/06 12:51:34 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colors.hpp"
#include "Wagner.hpp"
# include "UserSocket.hpp"

Wagner::Wagner()
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner constructor called" << RESET << std::endl;
	_cmd.insert(std::make_pair("NICK", cmd_nick));
	_cmd.insert(std::make_pair("USER", cmd_user));
	_cmd.insert(std::make_pair("PING", cmd_ping));
	_cmd.insert(std::make_pair("QUIT", cmd_quit));
	_cmd.insert(std::make_pair("WHOIS", cmd_whois));
	_cmd.insert(std::make_pair("MODE", cmd_mode));
	_cmd.insert(std::make_pair("PRIVMSG", cmd_privmsg));
	_cmd.insert(std::make_pair("KICK", cmd_kick));
	_cmd.insert(std::make_pair("INVITE", cmd_invite));
	_cmd.insert(std::make_pair("TOPIC", cmd_topic));
}

Wagner::~Wagner()
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner destructor called" << RESET << std::endl;
	// delete [] _events_list;
}


void 			Wagner::addUser(UserSocket *  user)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	_UserSockets.push_back(user);
}

t_response const * 	Wagner::treatRequest(t_request const & request)
{
	(void)request;

	std::string cmd = "NICK";
	std::map<std::string,pfonc>::iterator c_it;
	std::map<std::string,pfonc>::iterator c_ite = _cmd.end();
	
	
	UserSocket	*user = _UserSockets.front();

	c_it = _cmd.find(cmd);
	if (c_it != c_ite)
	{
		(c_it->second)(*user, request);
	}
	else
	{
		std::cout << MAGENTA << "Wagner :: CMD NOT FOUND" << RESET << std::endl;
	}
	
	
	
	// Analyse la CMD
	// traite la CMD (appel de fct membre)
		// NICK -> addUser( new User(t_request const & request ))
		// USER -> upd(user)
	// (! check si pb de traitement, verifier les erreurs de retour )

	// if CMD == NICK || USER
		// get &userSocket from request in _UserSockets
		// user->upddate(request)
	// "NICK" => NickMethod(request);
	return NULL;
}



bool	Wagner::cmd_nick(UserSocket & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}

bool	Wagner::cmd_user(UserSocket & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}

bool	Wagner::cmd_ping(UserSocket & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	//(void)user;
	user.pong();
	return (true);
}

bool	Wagner::cmd_quit(UserSocket & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}

bool	Wagner::cmd_whois(UserSocket & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}

bool	Wagner::cmd_mode(UserSocket & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}

bool	Wagner::cmd_join(UserSocket & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}

bool	Wagner::cmd_privmsg(UserSocket & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}

bool	Wagner::cmd_kick(UserSocket & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}

bool	Wagner::cmd_invite(UserSocket & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}

bool	Wagner::cmd_topic(UserSocket & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}
