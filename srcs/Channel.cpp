/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/17 17:02:47 by yboudoui         ###   ########.fr       */
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

void	Channel::send(User* user, std::string message)
{
	std::string	param, msg;
	t_users_map::iterator	it = _users_map.begin();

	param = ":" + user->getUsername();
	param += " PRIVMSG ";
	param += "#" + _name;
	param += " " + message;
	for (; it != _users_map.end(); it++)
	{
		if (it->first == user)
			continue;
		Message tmp(param);
		msg << tmp;
		it->first->setSendCache(msg);
	}
}

ChannelMap::ChannelMap()
{

}

ChannelMap::~ChannelMap()
{

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
	Channel					output;

	it = _channel_map.find(name);
	if (it == _channel_map.end())
		it = _channel_map.insert(std::make_pair(name, new Channel(name))).first;
	return (it->second);
}
