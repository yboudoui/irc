/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/06 14:34:39 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Colors.hpp"
# include "Wagner.hpp"
# include "SocketConnection.hpp"

Wagner::Wagner()
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner constructor called" << RESET << std::endl;
	_cmd.insert(std::make_pair("CAP", cmd_cap));
	_cmd.insert(std::make_pair("NICK", cmd_nick));
	_cmd.insert(std::make_pair("USER", cmd_user));
	_cmd.insert(std::make_pair("PING", cmd_ping));
	_cmd.insert(std::make_pair("QUIT", cmd_quit));
	_cmd.insert(std::make_pair("WHOIS", cmd_whois));
	_cmd.insert(std::make_pair("MODE", cmd_mode));
	_cmd.insert(std::make_pair("JOIN", cmd_join));
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


void 			Wagner::addUser(SocketConnection *  user)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	_SocketConnections.push_back(user);
}

void 	Wagner::treatRequest(SocketConnection & socket, t_request_queue const & _requests)
{
	(void)socket;
	(void)_requests;
	
	std::map<std::string,pfonc>::iterator it;
	std::map<std::string,pfonc>::iterator ite = _cmd.end();
	
	for (size_t idx = 0; idx < _requests.size(); idx += 1)
	{
		it = _cmd.find(_requests[idx].command.command);
		if (it != ite)
			(it->second)(socket, _requests[idx]);
		else
		{
			if (DEBUG)
				std::cout << MAGENTA << "Wagner::cmd not found [" << _requests[idx].command.command << "]" <<  std::endl;
			// cmd not found >> socket
		}
	}

	// Analyse la CMD
	// traite la CMD (appel de fct membre)
		// NICK -> addUser( new User(t_request const & request ))
		// USER -> upd(user)
	// (! check si pb de traitement, verifier les erreurs de retour )

	// if CMD == NICK || USER
		// get &SocketConnection from request in _SocketConnections
		// user->upddate(request)
	// "NICK" => NickMethod(request);
}



bool	Wagner::cmd_nick(SocketConnection & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}

bool	Wagner::cmd_user(SocketConnection & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}

bool	Wagner::cmd_ping(SocketConnection & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}

bool	Wagner::cmd_quit(SocketConnection & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}

bool	Wagner::cmd_whois(SocketConnection & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}

bool	Wagner::cmd_mode(SocketConnection & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}

bool	Wagner::cmd_join(SocketConnection & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}

bool	Wagner::cmd_privmsg(SocketConnection & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}

bool	Wagner::cmd_kick(SocketConnection & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}

bool	Wagner::cmd_invite(SocketConnection & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}

bool	Wagner::cmd_topic(SocketConnection & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}
bool	Wagner::cmd_cap(SocketConnection & user, t_request const &request)
{
	if (DEBUG)
		std::cout << MAGENTA << "Wagner::" <<__FUNCTION__ << RESET << std::endl;
	(void)request;
	(void)user;
	return (true);
}
