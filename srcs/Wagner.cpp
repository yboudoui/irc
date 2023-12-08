/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/08 12:11:27 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Colors.hpp"
# include "Wagner.hpp"
# include "User.hpp"
#include <stdlib.h>
# include "SocketConnection.hpp"

class USer;
# define DEBUG_CALL_WAGNER PRINT_DEBUG_CALL(MAGENTA, Wagner)
Wagner::Wagner(std::string host, int port, std::string pass)  : _hostname(host), _port(port), _pass(pass)
{
	DEBUG_CALL_WAGNER
	(void)port;
	_cmd.insert(std::make_pair("PASS",		&Wagner::cmd_pass));
	_cmd.insert(std::make_pair("CAP",		&Wagner::cmd_cap));
	_cmd.insert(std::make_pair("NICK",		&Wagner::cmd_nick));
	_cmd.insert(std::make_pair("USER",		&Wagner::cmd_user));
	_cmd.insert(std::make_pair("PING",		&Wagner::cmd_ping));
	_cmd.insert(std::make_pair("QUIT",		&Wagner::cmd_quit));
	_cmd.insert(std::make_pair("WHOIS",		&Wagner::cmd_whois));
	_cmd.insert(std::make_pair("MODE",		&Wagner::cmd_mode));
	_cmd.insert(std::make_pair("JOIN",		&Wagner::cmd_join));
	_cmd.insert(std::make_pair("PRIVMSG",	&Wagner::cmd_privmsg));
	_cmd.insert(std::make_pair("KICK",		&Wagner::cmd_kick));
	_cmd.insert(std::make_pair("INVITE",	&Wagner::cmd_invite));
	_cmd.insert(std::make_pair("TOPIC",		&Wagner::cmd_topic));
}

Wagner::~Wagner()
{
	DEBUG_CALL_WAGNER
	// delete [] _events_list;
}

void 			Wagner::addClient(SocketConnection*  socket)
{
	DEBUG_CALL_WAGNER
	if (socket == NULL)
		return ;
	_clients.insert(std::make_pair(socket, new User()));
}

t_message_queue	Wagner::treatRequest(SocketConnection* socket, t_message_queue& requests)
{
	t_message_queue	responses;
	t_message		curr_req;
	(void)socket;

	std::map<std::string,pfonc>::iterator it;
	std::map<std::string,pfonc>::iterator ite = _cmd.end();

	if (!requests.empty())
		PRINT_DEBUG_MESSAGE(MAGENTA,	"treatRequest[" << socket->getFd() << "]")
	
	while (!requests.empty())
	{
		curr_req = requests.front();
		requests.pop_front();
		it = _cmd.find(curr_req.command.name);
		if (it != ite)
		{
			pfonc	function = (it->second);
			try
			{
				t_message	response = (this->*function)(socket, curr_req);
				PRINT_DEBUG_MESSAGE(BLUE,	"\t[" << curr_req << "]")
				PRINT_DEBUG_MESSAGE(GREEN,	"\t[" << response << "]")
				responses.push_back(response);
			}
			catch(const std::exception& e)
			{
				std::cerr << RED << e.what() << "\n" << RESET;
				throw std::runtime_error(e.what());	

				return (responses);
			}
			
			

		}
		else {
			PRINT_DEBUG_MESSAGE(
			MAGENTA, "Wagner::cmd not found [" << curr_req.command.name << "]")
		}
	}

	// Analyse la CMD
	// traite la CMD (appel de fct membre)
		// NICK -> addUser( new User(t_message const & request ))
		// USER -> upd(user)
	// (! check si pb de traitement, verifier les erreurs de retour )

	// if CMD == NICK || USER
		// get &SocketConnection from request in _SocketConnections
		// user->upddate(request)
	// "NICK" => NickMethod(request);
	return (responses);
}


t_message	Wagner::cmd_cap(SocketConnection* socket, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = true };

	(void)request;
	(void)socket;
	return (output);
}


t_message	Wagner::cmd_pass(SocketConnection* socket, t_message const &request)
{
	(void)_port;
	DEBUG_CALL_WAGNER
	PRINT_DEBUG_MESSAGE(MAGENTA, request.params)

	t_message	output = {.valide = false };
	
	std::string _inpass = request.params.front();
	if (_inpass != _pass)
	{
		//output.command.code = "001";
		//output.params.push_back(":connection refused");
		delete socket;
		throw std::runtime_error("Socket Connection refused");
	}
	return (output);
}


t_message	Wagner::cmd_nick(SocketConnection* socket, t_message const &request)
{
	DEBUG_CALL_WAGNER
	PRINT_DEBUG_MESSAGE(MAGENTA, request.params)

	t_message	output = {.valide = true };
	std::string _inNick = request.params.front();

	User* _user = (_clients.find(socket))->second;

	_user->setNickname(_inNick);
	output.command.code = "001"; //001 Welcome to the Internet Relay Network <nick>!<user>@<host>
	output.params.push_back(_user->getNickname());
	output.params.push_back(":Welcome to the Internet Relay Network");	
	
	/* ERROR MANAGEMENT  username already exists*/ 
	// output.command.code = "433"; //433 ERR_NICKNAMEINUSE
	// output.params.push_back("nick");
	// output.params.push_back(":Nickname is already in use");	
	/*****/


	/* ANNOUNCE ARRIVAL 
	SocketConnection*		_clientSocket;
	User*					_clientUser;
	t_message	_clientOutput = {.valide = true };
	
	
	output.params.push_back(_user->getNickname());
	output.params.push_back(":A new user arrived");	

	std::map<SocketConnection*,	User*>::iterator	it;
	std::map<SocketConnection*,	User*>::iterator	ite = _clients.end();


	for ( ; it != ite ; it++)
	{
		_clientSocket = it->first;
		_clientUser = it->second;
		std::cout << _clientUser->getNickname() << std::endl;
	}
	*/

	return (output);
}

t_message	Wagner::cmd_user(SocketConnection* socket, t_message const &request)
{
	DEBUG_CALL_WAGNER
	PRINT_DEBUG_MESSAGE(MAGENTA, request.params)
	
	t_message	output = {.valide = true };
	
	if (request.params.empty())
	{
		// error throw ???
	}
	else
	{
		User*	_user = (_clients.find(socket))->second;
		size_t	size = request.params.size();
		if (size != 4)
		{
			// error throw ???
		}
		else
		{
			for (size_t idx = 0; idx < size; idx++)
			{
				switch (idx)
				{
					case 0 : _user->setUsername(request.params[idx]); 	break;
					case 1 : _user->setHostname(request.params[idx]); 	break;
					case 2 : _user->setServername(request.params[idx]);	break;
					case 3 : _user->setRealname(request.params[idx]);	break;
					default: break;
				}
			}
		}
	}
	return (output);
}

t_message	Wagner::cmd_ping(SocketConnection* socket, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = true };
	(void)request;
	(void)socket;

	output.command.name = "PONG";
	output.params.push_back(_hostname);
	return (output);
}

t_message	Wagner::cmd_quit(SocketConnection* socket, t_message const &request)
{
	DEBUG_CALL_WAGNER
	PRINT_DEBUG_MESSAGE(MAGENTA, request.params)

	t_message	output = {.valide = false };
	(void)request;
	(void)socket;
	//delete socket;
//	throw std::runtime_error("Socket Connection ended !");	
	return (output);
}

t_message	Wagner::cmd_whois(SocketConnection* socket, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = true };
	(void)request;

	output.command.code = "311";
//	output.command.name = "RPL_WHOISUSER";
//	<nick> <user> <host> * :<real_name>
	User*	_user = (_clients.find(socket))->second;
	
	output.params.push_back(_user->getNickname());
	output.params.push_back(_user->getUsername());
	output.params.push_back(_user->getHostname());
//	output.params.push_back("*");
	output.params.push_back(_user->getRealname());
	return (output);
}

t_message	Wagner::cmd_mode(SocketConnection* socket, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = false };
	(void)request;
	(void)socket;
	return (output);
}

t_message	Wagner::cmd_join(SocketConnection* socket, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = false };
	(void)request;
	(void)socket;
	return (output);
}

t_message	Wagner::cmd_privmsg(SocketConnection* socket, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = false };
	(void)request;
	(void)socket;
	return (output);
}

t_message	Wagner::cmd_kick(SocketConnection* socket, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = false };
	(void)request;
	(void)socket;
	return (output);
}

t_message	Wagner::cmd_invite(SocketConnection* socket, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = false };
	(void)request;
	(void)socket;
	return (output);
}

t_message	Wagner::cmd_topic(SocketConnection* socket, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = false };
	(void)request;
	(void)socket;
	return (output);
}
