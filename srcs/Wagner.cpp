/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/20 07:13:23 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "Wagner.hpp"
# include <vector>

Wagner::Wagner(std::string host, std::string pass)
	: _hostname(host)
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

void	Wagner::addEventListener(IQueue &queue, int fd_socketBind)
{
	DEBUG_CALL_WAGNER
	User*	user = new User(queue, fd_socketBind);
	if (user == NULL)
		return ; // error
	_clients.insert(user); //sure?
}

void	Wagner::treatEventListener(IQueue::IEventListener* listener)
{
	user = dynamic_cast<User*>(listener);
	if (user == NULL)
		throw std::runtime_error("Bad EventListener");
	Message::color(BLUE);
	requests << user->getReadCache();
	Message::color(GREEN);

	reply.setUser(user);
	reply.setHostName(_hostname);

	while (!requests.empty() && user->is_alive())
	{
		request = requests.getLastMessage();
		if (request == NULL)
		{
			PRINT_DEBUG_MESSAGE(CYAN, "WTF");
			continue;
		}
		reply.setRequest(request);
		t_cmd_map::iterator	it = _cmd.find(request->command.name);
		if (it != _cmd.end())
			(this->*(it->second))();
		else
			cmd_notFound();
	}
}

void	Wagner::cmd_notFound	(void)
{
	DEBUG_CALL_WAGNER
	reply(Response::_263);
}

void	Wagner::cmd_ping(void)
{
	DEBUG_CALL_WAGNER
	reply(Response::PONG);
}

void	Wagner::cmd_quit(void)
{
	DEBUG_CALL_WAGNER
	// TODO : envoyer message d'info aux autres utilisateurs
	user->is_alive(false);
}

void	Wagner::cmd_whois(void)
{
	DEBUG_CALL_WAGNER
	reply(Response::RPL_WHOISUSER);
}

void	Wagner::cmd_join(void)
{
	DEBUG_CALL_WAGNER

	if (request->params.empty())
		return (reply(Response::ERR_NEEDMOREPARAMS));

	std::vector< std::pair<std::string, available<std::string> > >	m;
	std::pair<std::string, available<std::string> >					new_pair;
	std::string														name;
	available<std::string>											password;
	size_t															index;

	for (index = 0; index < request->params.size(); index++)
	{
		name = request->params[index];
		if (name[0] != '#' && name[0] != '&')
			break ;
		new_pair.first = name.substr(1);
		m.push_back(new_pair);
	}

	for (size_t i = 0; i < m.size() && index < request->params.size(); i++)
		m[i].second(request->params[index++]);

/*	if (index < request.params.size())
		There is still some parameters.. error */

	for (size_t i = 0; i < m.size(); i++)
		_channel_map.find_or_create(m[i].first)->join(user);
}

void	Wagner::cmd_privmsg(void)
{
	DEBUG_CALL_WAGNER

	std::string	receiver, message = request->params.back();
	request->params.pop_back();

	reply.setMessage(message);
	while (!request->params.empty())
	{
		receiver = request->params.front().substr(1);
		request->params.pop_front();
		if (_channel_map.send(receiver, user, reply) == false)
			continue; // but still an error or message to someone
	}
}

void	Wagner::cmd_kick(void)
{
	DEBUG_CALL_WAGNER
}

void	Wagner::cmd_invite(void)
{
	DEBUG_CALL_WAGNER
}

void	Wagner::cmd_topic(void)
{
	DEBUG_CALL_WAGNER
}

void	Wagner::cmd_mode(void)
{
	DEBUG_CALL_WAGNER
}
