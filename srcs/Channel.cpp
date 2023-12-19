/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/19 12:32:14 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel()
{
	DEBUG_CALL_CHANNEL
}

Channel::Channel(std::string name)
	: _name(name)
{
	DEBUG_CALL_CHANNEL
}

Channel::~Channel()
{
	DEBUG_CALL_CHANNEL
}

void	Channel::join(User* user)
{
	if (user == NULL)
		return ;
	t_users_map::iterator it = _users_map.find(user);
	if (it == _users_map.end())
		_users_map.insert(std::make_pair(user, NONE));
}
/*
void	Channel::send(IOrchestrator::Context& ctx)
{
	IQueue::IEventListener*	listener = ctx.eventListener(NULL);
	for (t_users_map::iterator it = _users_map.begin(); it != _users_map.end(); it++)
	{
		if (it->first == listener)
			continue;
		ctx.eventListener(it->first);
		ctx.send();
	}
	ctx.eventListener(listener);
}
*/
void	Channel::send(User* user, Response reply)
{
	reply.setChannel(this);
	for (t_users_map::iterator it = _users_map.begin(); it != _users_map.end(); it++)
	{
		if (it->first == user)
			continue;
		reply.setUser(it->first);
		reply(Response::PRIVMSG);
	}
}

std::string	Channel::getName(void)
{
	return _name;
}


ChannelMap::ChannelMap()
{

}

ChannelMap::~ChannelMap()
{

}

bool		ChannelMap::send(std::string name, User* user, Response reply)
{
	Channel*	channel = find(name);
	if (channel == NULL)
		return (false);
	channel->send(user, reply);
	return (true);
}

Channel*	ChannelMap::find(std::string name)
{
	t_channel_map::iterator	it;

	it = _channel_map.find(name);
	if (it == _channel_map.end())
		return (NULL);
	return (it->second);
}

Channel*	ChannelMap::find_or_create(std::string name)
{
	t_channel_map::iterator	it;

	it = _channel_map.find(name);
	if (it == _channel_map.end())
		it = _channel_map.insert(std::make_pair(name, new Channel(name))).first;
	return (it->second);
}

