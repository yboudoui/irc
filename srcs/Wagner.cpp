/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/12 12:31:27 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Wagner.hpp"
# include <cstdlib>
Wagner::Wagner(std::string host, int port, std::string pass)
	: _hostname(host)
	, _port(port)
	, _pass(pass)
{
	DEBUG_CALL_WAGNER
	_cmd.insert(std::make_pair("CAP",		&Wagner::cmd_cap));
	
	_cmd.insert(std::make_pair("PASS",		&Wagner::cmd_pass));
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
/*
Command: ERROR
Parameters: <reason>

This message is sent from a server to a client to report a fatal error,
before terminating the client’s connection.
This MUST only be used to report fatal errors.
Regular errors should use the appropriate numerics or the IRCv3 standard replies framework.
*/
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

	std::map<std::string,pfonc>::iterator ite = _cmd.end();
	std::map<std::string,pfonc>::iterator it = ite;

	if (!requests.empty())
		PRINT_DEBUG_MESSAGE(MAGENTA,	"treatRequest[" << socket->getFd() << "]")
	while (!requests.empty())
	{
		curr_req = requests.front();
		requests.pop_front();
		if (curr_req != NULL)
			it = _cmd.find(curr_req->command.name);
		if (it != ite)
		{
			pfonc	function = (it->second);
			
			Message	*response = new Message((this->*function)(socket, *curr_req));
			PRINT_DEBUG_MESSAGE(BLUE,	"\t[" << curr_req << "]")
			if (response->valide)
				responses.push_back(response);
		}
		else
		{
			Message			output;
			std::string		params;
			
			output.valide = true;
			params = ":" + _hostname + " " + "263" + " " + curr_req->command.name + ": Unknown command: " + curr_req->command.name;
			output >> params;
			responses.push_back(new Message(output));	
			/*
			TODO =>
			RPL_TRYAGAIN (263) <command> :<info> 
			When a server drops a command without processing it,it MUST use this reply.
			*/
		}
	}
	PRINT_DEBUG_MESSAGE(MAGENTA, "Wagner::treatRequest end()")
	return (responses);
}

Message	Wagner::cmd_cap(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER
	Message	output;

	(void)request;
	(void)socket;
	return (output);
}


Message	Wagner::cmd_pass(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER

	Message		output;
	std::string	params;
	std::string	clientPass = request.params.front();

	if (request.params.empty() || clientPass == "")
	{
		/*
		TODO => ??? verifier que le pass n'est pas une chaine vide
		ERR_NEEDMOREPARAMS (461) <command> :<reason> ""
		Returned by the server by any command which requires more parameters than the number of parameters given
		*/
		params = ":" + _hostname + " " + "461" + " PASS : command requires more parameters";
		output >> params;
		socket->is_alive(false);
	}
	else if (clientPass != _pass)
	{
		/*
		ERR_PASSWDMISMATCH (464) :<reason> 
		Returned by the PASS command to indicate the given password was required and was either not given or was incorrect
		*/
		params = ":" + _hostname + " " + "464" + " : A Password is requiered to connect to " + _hostname;
		output >> params;
		socket->is_alive(false);
	}
	else
	{
		User* _user = (_clients.find(socket))->second;
		_user->connectionStep();
	}
	return (output);
}


Message	Wagner::cmd_nick(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER

	Message		output;
	std::string	_inNick = request.params.front();
	User*		_user = (_clients.find(socket))->second;

	std::string UserNickname = request.params.front();
	std::cout << "UserNickname : " <<  UserNickname << std::endl;
	/* STEP #1 : check if the new nickname is already in use || */
	if (request.params.empty())
	{
		// del socket->is_alive(false);
		/*
		TODO => 
		ERR_NONICKNAMEGIVEN (431) :<reason> 
		Returned when a nickname parameter expected for a command isn't found
		*/
	}
	else if (UserNickname == "anonymous"
		||  UserNickname.find_first_of("!%#@ ") != std::string::npos)
	{
		// del socket->is_alive(false);
		/*
		TODO => 
		ERR_ERRONEUSNICKNAME (432) <nick> :<reason> 
		Returned after receiving a NICK message which contains a nickname which is considered invalid
		such as it's reserved ('anonymous') or contains characters considered invalid for nicknames.
		*/		
	}
	else
	{
		/* STEP #2 : check if the new nickname is already in use */
		std::map<SocketConnection*,	User*>::iterator	clientIt = _clients.begin();
		std::map<SocketConnection*,	User*>::iterator	clientIte = _clients.end();
		while (clientIt != clientIte)
		{
			if (clientIt->second->getUsername() == UserNickname)
			{
				/*
				socket->is_alive(false);
				TODO => 
				ERR_NICKNAMEINUSE (433) <nick> :<reason> 
				Returned by the NICK command when the given nickname is already in use
				*/
				break ;
				return output;
				
			}
			clientIt++;
		}
		std::cout << "setNickname()" << std::endl;

		_user = (_clients.find(socket))->second;
		_user->setNickname(UserNickname);
		_user->connectionStep();
	}
	return (output);
}

Message	Wagner::cmd_user(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER
	
	Message			output;
	size_t			size = request.params.size();
	User*			_user = (_clients.find(socket))->second;
	std::string		params;

	output.valide = false;

	if (request.params.empty() || request.params.size() < 4)
	{
		socket->is_alive(false);
		/*
		TODO =>
		ERR_NEEDMOREPARAMS (461) <command> :<reason> ""
		Returned by the server by any command which requires more parameters than the number of parameters given
		*/
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
		_user->connectionStep();
	}


	if (_user->isConnected())
	{
		Message	greeting_001, greeting_002, greeting_003, greeting_004, greeting_005;

		greeting_001.valide = true;
		params = ":" + _hostname + " " + "001" + " : Welcome to the Internet Relay Network <nick>!<user>@<host>";
		greeting_001 >> params;
		socket->insertResponse(greeting_001);
	
		greeting_002.valide = true;
		params = ":" + _hostname + " " + "002" + " : Your host is <servername>, running version <version>";
		greeting_002 >> params;
		std::cout << greeting_002.prefixe.value.server_name.value;
		socket->insertResponse(greeting_002);
		
		greeting_003.valide = true;
		params = ":" + _hostname + " " + "003" + " : This server was created <date>";
		greeting_003 >> params;
		socket->insertResponse(greeting_003);

		greeting_004.valide = true;
		params = ":" + _hostname + " " + "004" + " : <server_name> <version> <user_modes> <chan_modes>";
		greeting_004 >> params;
		socket->insertResponse(greeting_004);
	
		greeting_005.valide = true;
		params = ":" + _hostname + " " + "005";
		greeting_005 >> params;

		return (greeting_005);
		/* post-registration greeting

		Upon successful completion of the registration process,
		the server MUST send, in this order, 
			the RPL_WELCOME (001),
			RPL_YOURHOST (002),
			RPL_CREATED (003),
			RPL_MYINFO (004),
			and at least one RPL_ISUPPORT (005) numeric to the client. 
			
		The server SHOULD then respond as though the client sent the LUSERS
		command and return the appropriate numerics. If the user has client 
		modes set on them automatically upon joining the network, 
		
		the server SHOULD send the client 
			the RPL_UMODEIS (221) reply
			or a MODE message with the client as target,
		preferably the former.
		
		The server MAY send other numerics and messages.
		
		The server MUST then respond as though the client sent it the MOTD command,
		
		i.e. it must send either the successful Message of the Day numerics or the ERR_NOMOTD (422) numeric.


		TODO =>
		RPL_WELCOME		(001) :Welcome to the Internet Relay Network <nick>!<user>@<host>
		RPL_YOURHOST	(002) :Your host is <servername>, running version <version> 
		RPL_CREATED		(003) :This server was created <date>
		RPL_MYINFO		(004) :<server_name> <version> <user_modes> <chan_modes> 
		RPL_ISUPPORT	(005)
		*/	
	}
	else
	{
		output.valide = true;
		params = ":" + _hostname + " " + "464" + " : A Password is requiered to connect to " + _hostname;
		output >> params;		
		socket->is_alive(false);
		/* la seule possibilite est qu'il manque le pass 
		TODO =>
		ERR_NEEDMOREPARAMS (461) <command> :<reason> ""
		Returned by the server by any command which requires more parameters than the number of parameters given
		*/	
	}

	
	/* ANNOUNCE ARRIVAL 
	SocketConnection*		_clientSocket;
	User*					_clientUser;

	Message	_clientOutput;
	
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
	*/

	return (output);
}

Message	Wagner::cmd_ping(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER
	Message			output;
	std::string		params;
	(void)request;
	(void)socket;

	params = ":" + _hostname + " " + "PONG " + _hostname;
	output >> params;
	//output >> ":" >> nickname >> "!" >> username >> "@" >> userhost;
	return (output);
}

Message	Wagner::cmd_quit(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER

	Message	output;
	
	(void)request;
	(void)socket;
	socket->is_alive(false);

	User* _user = (_clients.find(socket))->second;
	
	throw std::runtime_error(_user->getNickname() + " has quit the server !");	

	return (output);
}

Message	Wagner::cmd_whois(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER
	Message			output;
	std::string		params;

	(void)request;

//	"RPL_WHOISUSER";
	params = ":" + _hostname + " " + "311";
	output >> params;
	User*	_user = (_clients.find(socket))->second;
	
	output.params.push_back(_user->getNickname());
	output.params.push_back(_user->getUsername());
	output.params.push_back(_user->getHostname());
	output.params.push_back(_user->getRealname());
	return (output);
}

Message	Wagner::cmd_mode(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER
	Message	output;
	
	(void)request;
	(void)socket;
	return (output);
}

Message	Wagner::cmd_join(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER
	Message	output;
	
	(void)request;
	(void)socket;
	return (output);
}

Message	Wagner::cmd_privmsg(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER

	Message	output;
	
	(void)request;
	(void)socket;
	return (output);
}

Message	Wagner::cmd_kick(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER
	Message	output;
	
	(void)request;
	(void)socket;
	return (output);
}

Message	Wagner::cmd_invite(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER
	Message	output;
	
	(void)request;
	(void)socket;
	return (output);
}

Message	Wagner::cmd_topic(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER
	Message	output;
	
	(void)request;
	(void)socket;
	return (output);
}
