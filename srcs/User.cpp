/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/27 16:08:32 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(IQueue &queue, int fd)
	: SocketConnection(queue, fd)
	, _connection_complete(3)
{
	DEBUG_CALL_USER
}

User::~User()
{
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

void	User::join(Channel* channel, std::string password)
{
	if (channel == NULL)
		return ;
	channel->join(this, password);
	_channels.insert(std::make_pair(channel->name.get(), channel));
}

void	User::quit(Channel* channel)
{
	if (channel == NULL)
		return ;
	channel->remove(this);
	_channels.erase(channel->name.get());
}

bool	User::send(std::string channelName, std::string message)
{
	t_channels::iterator	it;

	it = _channels.find(channelName);
	if (it != _channels.end())
		return (it->second->send(nick_name.get(), message), true);
	return (false);
}

void	User::sendToAllChannels(std::string message)
{
	t_channels::iterator it = _channels.begin();

	for (; it != _channels.end(); it++)
		it->second->send(nick_name.get(), message);
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
