/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner_connection.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/15 18:38:26 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Wagner.hpp"

void	Wagner::cmd_cap(SocketConnection* socket, Message* request, t_message_queue& responses)
{
	DEBUG_CALL_WAGNER
	(void)request;
	(void)socket;
	(void)responses;
}

void	Wagner::cmd_pass(SocketConnection* socket, Message* request, t_message_queue& responses)
{
	DEBUG_CALL_WAGNER

	std::string		params;
	std::string		clientPass = request->params.front();

	if (request->params.empty() || clientPass == "")
	{
		if (socket->is_alive())
		{
			/*
			ERR_NEEDMOREPARAMS (461) <command> :<reason> ""
			Returned by the server by any command which requires more parameters than the number of parameters given
			*/
			params = ":" + _hostname + " " + "461" + " PASS : command requires more parameters";
			responses.push_back(new Message(params));
			socket->is_alive(false);
		}
	}
	else if (clientPass != _pass)
	{
		/*
		ERR_PASSWDMISMATCH (464) :<reason> 
		Returned by the PASS command to indicate the given password was required and was either not given or was incorrect
		*/
		params = ":" + _hostname + " " + "464" + " : A Password is requiered to connect to " + _hostname;
		responses.push_back(new Message(params));
		socket->is_alive(false);
	}
	else
	{
		User* _user = (_clients.find(socket))->second;
		_user->connectionStep();
	}
}

void	Wagner::cmd_nick(SocketConnection* socket, Message* request, t_message_queue& responses)
{
	DEBUG_CALL_WAGNER

	User*			_user;
	std::string		params;

	std::string UserNickname = request->params.front();
//	std::cout << "UserNickname : " <<  UserNickname << std::endl;
	/* STEP #1 : check if the new nickname is already in use || */
	if (request->params.empty())
	{
		if (socket->is_alive())
		{
			/*
			ERR_NONICKNAMEGIVEN (431) :<reason> 
			Returned when a nickname parameter expected for a command isn't found
			*/
			params = ":" + _hostname + " " + "431" + " : a nickname parameter is expected";
			responses.push_back(new Message(params));
			socket->is_alive(false);
		}
	}
	else if (UserNickname == "anonymous"
		||  UserNickname.find_first_of("!%#@") != std::string::npos)
	{
		if (socket->is_alive())
		{
			/*
			ERR_ERRONEUSNICKNAME (432) <nick> :<reason> 
			Returned after receiving a NICK message which contains a nickname which is considered invalid
			such as it's reserved ('anonymous') or contains characters considered invalid for nicknames.
			*/
			params = ":" + _hostname + " " + "432" + " " + UserNickname + " : invalid nickname";
			responses.push_back(new Message(params));
			socket->is_alive(false);
		}
	}
	else
	{
		/* STEP #2 : check if the new nickname is already in use */
		std::map<SocketConnection*,	User*>::iterator	clientIt = _clients.begin();
		std::map<SocketConnection*,	User*>::iterator	clientIte = _clients.end();
		while (clientIt != clientIte)
		{
			if (clientIt->second->getNickname() == UserNickname)
			{
				if (socket->is_alive())
				{
					/*
					ERR_NICKNAMEINUSE (433) <nick> :<reason> 
					Returned after receiving a NICK message which contains a nickname which is considered invalid
					such as it's reserved ('anonymous') or contains characters considered invalid for nicknames.
					*/
					params = ":" + _hostname + " " + "432" + " " + UserNickname + " :nickname alreasy in use";
					responses.push_back(new Message(params));
					socket->is_alive(false);
				}
				return ;
			}
			clientIt++;
		}
		_user = (_clients.find(socket))->second;
		_user->setNickname(UserNickname);
		_user->connectionStep();
	}
}

void	Wagner::cmd_user(SocketConnection* socket, Message* request, t_message_queue& responses)
{
	DEBUG_CALL_WAGNER

	size_t			size = request->params.size();
	User*			_user = (_clients.find(socket))->second;
	std::string		params;

	if (size == 0 || size < 4)
	{
		/*
		TODO =>
		ERR_NEEDMOREPARAMS (461) <command> :<reason> ""
		Returned by the server by any command which requires more parameters than the number of parameters given
		*/
		params = ":" + _hostname + " " + "461" + " USER : User command needs more parameters";
		responses.push_back(new Message(params));
		socket->is_alive(false);
	}
	else
	{
		for (size_t idx = 0; idx < size; idx++)
		{
			switch (idx)
			{
				case 0 : _user->setUsername(request->params[idx]); 	break;
				case 1 : _user->setHostname(request->params[idx]); 	break;
				case 2 : _user->setServername(request->params[idx]);	break;
				case 3 : _user->setRealname(request->params[idx]);	break;
				default: break;
			}
		}
		_user->connectionStep();
	}

	if (_user->isConnected())
	{
		User*		_user = (_clients.find(socket))->second;

		params = ":" + _hostname + " " + "001 "
			+ _user->getNickname() 
			+ " :Welcome to the Internet Relay Network " 
			+ _user->getNickname() + "!" + _user->getUsername() + "@" + _user->getHostname() + "";
		responses.push_back(new Message(params));

		params = ":" + _hostname + " " + "002" + " : Your host is <servername>, running version <version>";
		responses.push_back(new Message(params));

		params = ":" + _hostname + " " + "003" + " : This server was created <date>";
		responses.push_back(new Message(params));

		params = ":" + _hostname + " " + "004" + " : <server_name> <version> <user_modes> <chan_modes>";
		responses.push_back(new Message(params));

		params = ":" + _hostname + " " + "005";
		responses.push_back(new Message(params));
		_user->socket = socket;
		return ;
	}
	else if (socket->is_alive())
	{
		params = ":" + _hostname + " " + "464" + " : A Password is requiered to connect to " + _hostname;
		responses.push_back(new Message(params));
		socket->is_alive(false);
	}
}

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
