/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/02 18:00:01 by yboudoui         ###   ########.fr       */
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
	t_channel_map::iterator	chan;

	t_clients::iterator	it = _clients.begin();
	for ( ; it != _clients.end() ; it++)
	{
		delete *it;
		// FIXSEGFAULT removeEventListener(*it);
	}

	chan = _channel_map.begin();
	for ( ; chan != _channel_map.end() ; chan++)
		delete chan->second;


	/*
	TODO // send error_message 
	Command: ERROR
	Parameters: <reason>

	This message is sent from a server to a client to report a fatal error,
	before terminating the client’s connection.
	This MUST only be used to report fatal errors.
	Regular errors should use the appropriate numerics or the IRCv3 standard replies framework.
	*/
	DEBUG_CALL_WAGNER
}

void	Wagner::addEventListener(IQueue &queue, int fd_socketBind)
{
	PRINT_DEBUG_CALL_MESSAGE(YELLOW, "", Wagner, RESET << " -> ")
	User*	user = new User(queue, fd_socketBind);
	if (user == NULL)
		return ; // error
	_clients.insert(user);
}


void	Wagner::removeEventListener(IQueue::IEventListener* listener)
{
	PRINT_DEBUG_CALL_MESSAGE(YELLOW, "", Wagner, RESET << " -> ")
	User*	user = dynamic_cast<User*>(listener);

	t_clients::iterator it = _clients.find(user);
	if (it == _clients.end())
		return ;
	_clients.erase(it);
	IQueue::IEventListener::free(user);
}


void	Wagner::treatEventListener(IQueue::IEventListener* listener)
{
	MessageQueue	requests;

	user = dynamic_cast<User*>(listener);
	if (user == NULL)
		throw std::runtime_error("Bad EventListener");
	Message::color(BLUE);
	requests << user->getReadCache();
	Message::color(GREEN);

	while (!requests.empty() && user->is_alive())
	{
		request = requests.getLastMessage();
		if (request == NULL)
			continue ;
		t_cmd_map::iterator	it = _cmd.find(request->command.name);
		if (it != _cmd.end())
			(this->*(it->second))();
		else
			cmd_notFound(request->command.name);
		delete request;
	}
}

void	Wagner::cmd_notFound	(std::string name)
{
	DEBUG_CALL_WAGNER
	user->setSendCache(RPL_TRYAGAIN(name));
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
	{
		Channel*	new_channel = new Channel();
		new_channel->name = name;
		it = _channel_map.insert(std::make_pair(name, new_channel)).first;
	}
	return (it->second);
}
