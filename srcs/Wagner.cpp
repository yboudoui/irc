/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 16:12:23 by yboudoui         ###   ########.fr       */
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
	_clients.insert(user);
}

void	Wagner::treatEventListener(IQueue::IEventListener* listener)
{
	user = dynamic_cast<User*>(listener);
	if (user == NULL)
		throw std::runtime_error("Bad EventListener");
	Message::color(BLUE);
	if (user->getReadCache().size())
		std::cout << std::endl << RED << user->getReadCache() << std::endl << std::endl;
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

User*	Wagner::findClient(std::string name)
{
	t_clients::iterator	it = _clients.begin();
	t_clients::iterator	ite = _clients.end();

	for ( ; it != ite ; it++)
	{
		if ((*it)->nick_name.get() == name)
		{
			return *it;
		}
	}
	return (NULL);
}

Channel*	Wagner::find_channel(std::string name)
{
	t_channel_map::iterator	it;

	it = _channel_map.find(name);
	if (it == _channel_map.end())
		return (NULL);
	return (it->second);
}

Channel*	Wagner::find_or_create_channel(std::string name)
{
	t_channel_map::iterator	it;

	it = _channel_map.find(name);
	if (it == _channel_map.end())
		it = _channel_map.insert(std::make_pair(name, new Channel(name))).first;
	return (it->second);
}
