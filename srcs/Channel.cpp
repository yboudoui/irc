/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 14:10:14 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "responses.hpp"

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

bool	Channel::join(User* user, std::string usr_password)
{
	if (user == NULL)
		return true;
	
	t_users_map::iterator it = _users_map.find(user);
	if (it != _users_map.end() 
		&& (it->second == NONE || it->second == OPERATOR))
		return true;

	if (!_users_map.size())
		_users_map.insert(std::make_pair(user, OPERATOR));
	else if (this->canJoin(user, usr_password))
	{
		if (it == _users_map.end())
			_users_map.insert(std::make_pair(user, NONE));
		else
		{
			it->second = NONE;
			// modifier les droits user INVITED >> none
		}
	}
	else
		return false;
	return true;
}

void	Channel::send(std::string senderNickname, std::string message)
{
	(void)senderNickname;
	(void)message;
	for (t_users_map::iterator it = _users_map.begin(); it != _users_map.end(); it++)
	{
		if (it->first->getNickname() == senderNickname)
			continue;
		it->first->setSendCache(message);
	}
}

std::string	Channel::getName(void)
{
	return _name;
}

int	Channel::getLimit(void)
{
	return _userLimit;
}

std::string	Channel::getTopic(void)
{
	return _topic;
}


ChannelMap::ChannelMap()
{

}

ChannelMap::~ChannelMap()
{

}

void	ChannelMap::remove(User* user)
{
	if (user == NULL)
		return ;
//	_bimap.remove(user);
}

void	ChannelMap::remove(Channel* channel)
{
	if (channel == NULL)
		return ;
//	_bimap.remove(channel);
}

bool		ChannelMap::send(std::string channelName, std::string senderNickname, std::string message)
{
	Channel*	channel = find(channelName);
	if (channel)
		return (channel->send(senderNickname, message), true);
	return (false);
}

// TODO ??? 
bool		ChannelMap::sendToAllChannelOfUser(User* user, std::string message)
{
	(void)user;
	(void)message;
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

void Channel::setMode(char op, enum ChannelModes mode)
{
    if (op == '+')
        _modes |= mode;
    else
        _modes &= ~mode;
}

bool Channel::getMode(enum ChannelModes mode) {
    return (_modes & mode) != 0;
}

std::string Channel::getChannelModes() {
	std::string modes;

	if(this->getMode(INVITE_ONLY))
		modes.append("i");
	if(this->getMode(TOPIC_ONLY_OP))
		modes.append("t");
	if(this->getMode(KEY_PROTECTED))
		modes.append("k");
	if(this->getMode(USER_LIMIT))
		modes.append("l");
    return  modes;
}

void Channel::setKey(std::string pass)
{
    _key = pass;
}
void Channel::setTopic(std::string topic)
{
    _topic = topic;
}

void Channel::setLimit(int limit)
{
    _userLimit = limit;
}

bool Channel::isOperator(User* user)
{
	t_users_map::iterator	it = _users_map.begin();
	t_users_map::iterator	ite = _users_map.end();

	it = _users_map.find(user);
	if (it == ite)
		return false;
	if (it->second == OPERATOR)
		return true;
	return false;
}

bool Channel::isInChannel(User* user)
{
	t_users_map::iterator	it = _users_map.begin();
	t_users_map::iterator	ite = _users_map.end();

	it = _users_map.find(user);
	if (it == ite)
		return false;
	return true;
}


/*
ERR_INVITEONLYCHAN (473) //canJoin
<channel> :<reason>
Returned when attempting to join a channel which is invite only without an invitation

ERR_BADCHANNELKEY (475) //canJoin
<channel> :<reason>
Returned when attempting to join a key-locked
channel either without a key or with the wrong key

ERR_CHANNELISFULL (471) // canJoin
<channel> :<reason>
Returned when attempting to join
a channel which is set +l and is already full

*/
bool Channel::canJoin(User* user, std::string usr_password)
{
	if (getMode(KEY_PROTECTED))
	{
		if (usr_password != _key)
		{
			user->setSendCache(ERR_BADCHANNELKEY(getName()));
			return false;
		}
	}
	if (getMode(USER_LIMIT))
	{
		int nb_user = countUser();
		if (nb_user >= _userLimit)
		{
			user->setSendCache(ERR_CHANNELISFULL(getName()));
			return false;
		}
	}
	if (getMode(INVITE_ONLY))
	{
		t_users_map::iterator it = _users_map.find(user);
		if (it != _users_map.end() && it->second == INVITED)
			return true;
		return false;
	}
	// TODO check if the user can join the channel,
	// check channel mode INVITE_ONLY
	// check channel mode KEY_PROTECTED & password 
	// if true, check if the user has been invited by
	// an operator

	// 475 cannot join Channel () (KEY_PROTECTED)
	// 473 cannot join Channel () (INVITE_ONLY)
	// 464 bad channel key	(KEY_PROTECTED && usr_password != key)

	// check aslo channel user limit
	// !! delete user from user_map when he QUIT
	(void)user;
	(void)usr_password;
	return true;
}

int  Channel::countUser()
{
	t_users_map::iterator	it = _users_map.begin();
	t_users_map::iterator	ite = _users_map.end();
	
	int nb = 0;
	for ( ; it != ite ; it++)
	{
		if(it->second != INVITED)
			nb++;
	}
	return nb;
}

User * Channel::findUser(std::string nick)
{
	t_users_map::iterator	it = _users_map.begin();
	t_users_map::iterator	ite = _users_map.end();

	for ( ; it != ite ; it++)
	{
		if ((it->first)->getNickname() == nick)
			return it->first;
	}
	return NULL;
}
