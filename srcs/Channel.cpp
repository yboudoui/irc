/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/20 10:53:40 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel()
{
	_modes = 0;
	DEBUG_CALL_CHANNEL
}

Channel::Channel(std::string name)
	: _name(name), _modes(0)
{
	DEBUG_CALL_CHANNEL
}

Channel::~Channel()
{
	DEBUG_CALL_CHANNEL
}

// TODO if (this->canJoin(user, usr_password))
void	Channel::join(User* user, std::string usr_password)
{
	(void)usr_password;
	if (user == NULL)
		return ;
	t_users_map::iterator it = _users_map.find(user);
	if (it == _users_map.end())
		_users_map.insert(std::make_pair(user, NONE));
}

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
	if (channel)
		return (channel->send(user, reply), true);
	return (false);
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

#include <bitset>

void afficherEnBinaire(int nombre) {
	for (int i = sizeof(int) * 8 -1 ; i >= 0 ; i--)
	{
		int bit = (nombre >> i) & 1;
		std::cout << bit;
	}
}

void Channel::setMode(char op, enum ChannelModes mode)
{
	std::cout << "setMode 1 :" ;
	 afficherEnBinaire(_modes) ;
	std::cout << std::endl;
	{
    if (op == '+')
        _modes |= mode;
    else
        _modes &= ~mode;
	}
	std::cout << "setMode 2 :" ;
	 afficherEnBinaire(_modes) ;
	std::cout << std::endl;

}

bool Channel::getMode(enum ChannelModes mode) {
    return (_modes & mode) != 0;
}

void Channel::setKey(std::string pass)
{
    _key = pass;
}

void Channel::setLimit(int limit)
{
    _userLimit = limit;
}

bool Channel::isOperator(User* user)
{
	// TODO check the user rights,
	// if he can change the modes / kick /invite etc.
	(void)user;
	return true;
}

bool Channel::canJoin(User* user, std::string usr_password)
{
	// TODO check if the user can join the channel,
	// check channel mode INVITE_ONLY
	// check channel mode KEY_PROTECTED & password 
	// if true, check if the user has been invited by
	// an operator

	// 475 cannot join Channel () (KEY_PROTECTED)
	// 473 cannot join Channel () (INVITE_ONLY)
	// 464 bad channel key	(KEY_PROTECTED && usr_password != key)
	(void)user;
	(void)usr_password;
	return true;
}
