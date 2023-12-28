/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/28 14:50:20 by sethomas         ###   ########.fr       */
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
	t_channels::iterator	it = _channels.begin();

	for (; it != _channels.end(); it++)
	{
//		it->second->sendToAllChannels("quit", this);
		it->second->remove(this);
//		_channels.erase(it);
	}
	DEBUG_CALL_USER
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
	t_channels::iterator it = _channels.begin();
	for (; it != _channels.end(); it++)
	{
		it->second->remove(this);
		//_channels.erase(it->second->name);
	}
}

void	User::quit(Channel* channel)
{
	if (channel == NULL)
		return ;
//	channel->remove(this);
	_channels.erase(channel->name);
}

void	User::sendToAllChannels(std::string message)
{
	t_channels::iterator it = _channels.begin();

	std::string privmsg;

	for (; it != _channels.end(); it++)
	{	
		privmsg = PRIVMSG(nick_name.get(), it->second->name, message);
		std::cout << WHITE << privmsg << std::endl;
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
