/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 12:32:27 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Wagner.hpp"

Wagner::Wagner(std::string pass)
	: _pass(pass)
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
	for (t_clients::iterator it = _clients.begin() ; it != _clients.end() ; it++)
		delete *it;

	for (t_channel_map::iterator it = _channel_map.begin(); it != _channel_map.end() ; it++)
		delete it->second;
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
	user = dynamic_cast<User*>(listener);
	if (user == NULL)
		throw std::runtime_error("Bad EventListener");
	while (user->read_message(&request))
	{
		t_cmd_map::iterator	it = _cmd.find(request->command.name);
		if (it != _cmd.end())
			(this->*(it->second))();
		else
			cmd_unknown();
		delete request;
	}
}

User*		Wagner::findClient(std::string name)
{
	t_clients::iterator	it = _clients.begin();
	t_clients::iterator	ite = _clients.end();

	for ( ; it != ite ; it++)
	{
		if ((*it)->nick_name == name)
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
