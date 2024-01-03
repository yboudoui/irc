/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/03 18:24:14 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(IQueue &queue, int fd)
	: SocketConnection(queue, fd)
	, _connection_complete(2)
{
	DEBUG_CALL_USER
}

User::~User()
{
	quitAllChannels();
	DEBUG_CALL_USER_DESTRUCTOR
}

bool	User::isConnected() const
{
	return (_connection_complete == 0);
}

void	User::connectionStep()
{
	if (_connection_complete)
		_connection_complete--;
}


void	User::join(Channel* channel)
{
	if (channel == NULL)
		return ;
	_channels.insert(std::make_pair(channel->name, channel));
}


void	User::quitAllChannels(void)
{
	if (_channels.size())
	{
		t_channels::iterator it;
		t_channels::iterator ite = _channels.end();
		for (it = _channels.begin(); it != ite; it++)
		{
			if (it->second)
				it->second->remove(this);
		}
	}
}

void	User::quit(Channel* channel)
{
	if (channel == NULL)
		return ;
	_channels.erase(channel->name);
	channel->remove(this);
}

void	User::sendToAllChannels(std::string message)
{
	t_channels::iterator it = _channels.begin();

	std::string privmsg;

	for (; it != _channels.end(); it++)
	{	
		privmsg = PRIVMSG(nick_name.get(), it->second->name, message);
		it->second->send(nick_name.get(), privmsg);
	}
}

bool	User::send(std::string channelName, std::string message)
{
	t_channels::iterator	it;

	it = _channels.find(channelName);
	if (it != _channels.end())
		return (it->second->send(nick_name.get(), message), true);
	return (false);
}

void	User::sendTo(Channel* channel, std::string msg)
{
	if (channel == NULL)
		return ;
	if (_channels.find(channel->name) != _channels.end())
		channel->sendToAllUsers(msg, this);
}

bool	User::operator () (User* to_compare)
{
	return (to_compare == this);
}

predicate<User*>&	nickName(std::string nick_name)
{
	static std::string	_nick_name = nick_name;
	static struct : predicate<User*> {
		public:
			bool	operator () (User *input)
			{
				return (input && input->nick_name.get() == _nick_name);
			}
	}	predicate;
	return (predicate);
}
