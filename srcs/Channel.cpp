/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/13 19:05:40 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

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
	std::string	param;
	t_users_map::iterator	it = _users_map.begin();

	param = ":" + user->getUsername();
	param += " PRIVMSG ";
	param += "#" + _name;
	param += " " + message;
	for (; it != _users_map.end(); it++)
	{
		if (it->first == user)
			continue;
		Message	*new_msg = new Message(param);
		it->first->socket->insertResponse(new_msg);
	}
}

Channel& Channel::operator = (const Channel &other)
{
	_name = other._name;
	return (*this);
}
