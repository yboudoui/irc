/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 16:18:05 by yboudoui         ###   ########.fr       */
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
/*
void	sendToAllChannels(std::string senderNickname, std::string message)
{
	(void)senderNickname;
	(void)message;
	for (t_users_map::iterator it = _users_map.begin(); it != _users_map.end(); it++)
	{
		if (it->first->getNickname() == senderNickname)
			continue;
		it->first->setSendCache(message);
	}
}*/
