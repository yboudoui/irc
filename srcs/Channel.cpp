/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/12 16:05:13 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel()
{
	DEBUG_CALL_CHANNEL
}

Channel::Channel(t_channel_name name)
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
	t_user_name	name = user->getUsername();
	t_users_map::iterator it = _users_map.find(name);
	if (it == _users_map.end())
		_users_map.insert(std::make_pair(name, std::make_pair(user, NONE)));
}

Channel& Channel::operator = (const Channel &other)
{
	_name = other._name;
	return (*this);
}
