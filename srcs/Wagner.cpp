/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/11 15:54:52 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Wagner.hpp"

Wagner::Wagner(std::string host, int port, std::string pass)
	: _hostname(host)
	, _port(port)
	, _pass(pass)
{
	DEBUG_CALL_WAGNER
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
	Message			*curr_req;
	t_message_queue	responses;

	(void)socket;

	std::map<std::string,pfonc>::iterator it;
	std::map<std::string,pfonc>::iterator ite = _cmd.end();

	if (!requests.empty())
		PRINT_DEBUG_MESSAGE(MAGENTA,	"treatRequest[" << socket->getFd() << "]")
	while (!requests.empty())
	{
		curr_req = requests.front();
		requests.pop_front();
	
		it = _cmd.find(curr_req->command.name);
		if (it != ite)
		{
			pfonc	function = (it->second);
			try
			{
				Message	*response = new Message((this->*function)(socket, *curr_req));
				PRINT_DEBUG_MESSAGE(BLUE,	"\t[" << curr_req << "]")

				responses.push_back(response);
				PRINT_DEBUG_MESSAGE(GREEN,	"\t[" << response << "]")
			}
			catch(const std::exception& e)
			{
				throw std::runtime_error(e.what());	

				return (responses);
			}

		}
		else {
				// TODO envoyer PRIVMSG au socket
			PRINT_DEBUG_MESSAGE(
			MAGENTA, "Wagner::cmd not found [" << curr_req->command.name << "]")
		}
	}

	// Analyse la CMD
	// traite la CMD (appel de fct membre)
		// NICK -> addUser( new User(Message const & request ))
		// USER -> upd(user)
	// (! check si pb de traitement, verifier les erreurs de retour )

	// if CMD == NICK || USER
		// get &SocketConnection from request in _SocketConnections
		// user->upddate(request)
	// "NICK" => NickMethod(request);
	return (responses);
}

Message	Wagner::cmd_cap(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER
	Message	output;
	output.valide = true;

	(void)request;
	(void)socket;
	return (output);
}


Message	Wagner::cmd_pass(SocketConnection* socket, Message const &request)
{
	(void)_port;
	DEBUG_CALL_WAGNER

	Message	output;
	output.valide = true;
	
	std::string _inpass = request.params.front();
	if (_inpass != _pass)
		socket->is_alive(false);
	return (output);
}


Message	Wagner::cmd_nick(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER

	Message	output;
	output.valide = true;
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


	/* ANNOUNCE ARRIVAL */
	SocketConnection*		_clientSocket;
	User*					_clientUser;

	Message	_clientOutput;
	_clientOutput.valide = true;
	
	_clientOutput.command.name = "PRIVMSG"; //433 ERR_NICKNAMEINUSE

	std::map<SocketConnection*,	User*>::iterator	it = _clients.begin();
	std::map<SocketConnection*,	User*>::iterator	ite = _clients.end();


	for ( ; it != ite ; it++)
	{
		if (_clientSocket != socket)
		{
		_clientSocket = it->first;
		_clientUser = it->second;

		_clientOutput.params.push_back(_clientUser->getNickname());
		_clientOutput.params.push_back(": A new user arrived on the server, say hello to " +_user->getNickname()+ "");	
		_clientSocket->insertResponse(_clientOutput);
		_clientOutput.params.clear();
		std::cout << ":A new user arrived : " << _clientUser->getNickname() << std::endl;
		}
	}
	

	return (output);
}

Message	Wagner::cmd_user(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER
	
	Message	output;
	output.valide = true;

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


		/* check if*/
	}
	return (output);
}

Message	Wagner::cmd_ping(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER
	Message	output;
	output.valide = true;
	std::string u;
	u = "PONG" + _hostname;
	output >> u;
	(void)request;
	(void)socket;

	return (output);
}

Message	Wagner::cmd_quit(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER

	Message	output;
	output.valide = true;
	(void)request;
	(void)socket;
	socket->is_alive(false);
	//delete socket;
	User* _user = (_clients.find(socket))->second;
	throw std::runtime_error(_user->getNickname() + " has quit the server !");	
	return (output);
}

Message	Wagner::cmd_whois(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER
	Message	output;
	output.valide = true;
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

Message	Wagner::cmd_mode(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER
	Message	output;
	output.valide = false;
	(void)request;
	(void)socket;
	return (output);
}

Message	Wagner::cmd_join(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER
	Message	output;
	output.valide = false;
	(void)request;
	(void)socket;
	return (output);
}

Message	Wagner::cmd_privmsg(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER

	Message	output;
	output.valide = false;
	(void)request;
	(void)socket;
	return (output);
}

Message	Wagner::cmd_kick(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER
	Message	output;
	output.valide = false;
	(void)request;
	(void)socket;
	return (output);
}

Message	Wagner::cmd_invite(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER
	Message	output;
	output.valide = false;
	(void)request;
	(void)socket;
	return (output);
}

Message	Wagner::cmd_topic(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER
	Message	output;
	output.valide = false;
	(void)request;
	(void)socket;
	return (output);
}
