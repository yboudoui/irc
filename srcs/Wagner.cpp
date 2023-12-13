/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/13 15:56:31 by yboudoui         ###   ########.fr       */
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
//	_cmd.insert(std::make_pair("MODE",		&Wagner::cmd_mode));
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

void	Wagner::treatRequest(SocketConnection* socket, t_message_queue& requests, t_message_queue& responses)
{
	(void)socket;

	std::map<std::string,pfonc>::iterator ite = _cmd.end();
	std::map<std::string,pfonc>::iterator it = ite;

	while (!requests.empty() && socket->is_alive())
	{
		Message curr_req = requests.front();
		requests.pop_front();
		it = _cmd.find(curr_req.command.name);
		if (it != ite)
		{
			pfonc	function = (it->second);
			Message response = (this->*function)(socket, curr_req);
			if (response.valide)
				responses.push_back(response);
		}
		else
		{
			Message			output;
			std::string		params;
			/*
			RPL_TRYAGAIN (263) <command> :<info> 
			When a server drops a command without processing it,it MUST use this reply.
			*/
			output.valide = true;
			params = ":" + _hostname + " " + "263" + " " + curr_req.command.name + ": Unknown command: " + curr_req.command.name;
			output >> params;
			responses.push_back(output);
		}
	}
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
	return (output);
}

Message	Wagner::cmd_quit(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER

	Message	output;
	
	(void)request;
	(void)socket;
	socket->is_alive(false);
	// TODO : envoyer message d'info aux autres utilisateurs
	return (output);
}

Message	Wagner::cmd_whois(SocketConnection* socket, Message const &request)
{
	DEBUG_CALL_WAGNER
	Message			output;
	std::string		params;
	User*			_user = (_clients.find(socket))->second;

	(void)request;
	output.valide = true;

	//"RPL_WHOISUSER (311)";
	output.params.push_back(":"+_hostname);
	output.params.push_back("311");
	output.params.push_back(_user->getNickname());
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

/*
	if (request.pair.empty())
		ERR_NEEDMOREPARAMS
*/

	std::vector<t_channel_name_password>	m;
	t_channel_name_password					new_pair;
	t_channel_name							name;
	t_channel_password						password;
	size_t									index;

	for (index = 0; index < request.params.size(); index++)
	{
		name = request.params[index];
		if (name[0] != '#' && name[0] != '&')
			break ;
		new_pair.first = name.substr(1);
		m.push_back(new_pair);
	}

	for (size_t i = 0; i < m.size() && index < request.params.size(); i++)
		m[i].second(request.params[index++]);

/*
	if (index < request.params.size())
		There is still some parameters.. error
*/

	for (size_t i = 0; i < m.size(); i++)
	{
		name = m[i].first;
		t_channel_map::iterator it = _channel_map.find(name);
		if (it == _channel_map.end())
			_channel_map.insert(std::make_pair(name, new Channel(name)));
		_channel_map.find(name)->second->join(_clients[socket]);
	}
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
