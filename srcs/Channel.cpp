/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 18:06:30 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "responses.hpp"

Channel::Channel()
{
	_modes = 0;
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
		if (it->first->nick_name.get() == senderNickname)
			continue;
		it->first->setSendCache(message);
	}
}


void	Channel::remove(User* user)
{
	if (user == NULL)
		return ;
	//_users_map.remove >>
}

// TODO ??? 
/*
bool		ChannelMap::sendToAllChannelOfUser(User* user, std::string message)
{
	(void)user;
	(void)message;
	return (true);
}
*/
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

std::string Channel::getChannelModes()
{
	std::string modes;

	if(this->getMode(INVITE_ONLY))
		modes.append("i");
	if(this->getMode(TOPIC_ONLY_OP))
		modes.append("t");
	if(this->getMode(KEY_PROTECTED))
		modes.append("k");
	if(this->getMode(USER_LIMIT))
		modes.append("l");
	return (modes);
}

void Channel::setKey(std::string pass)
{
    _key = pass;
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

bool Channel::canJoin(User* user, std::string usr_password)
{
	if (getMode(KEY_PROTECTED))
	{
		if (_key && usr_password != _key())
		{
			user->setSendCache(ERR_BADCHANNELKEY(name.get()));
			return false;
		}
	}
	if (getMode(USER_LIMIT))
	{
		size_t nb_user = countUser();
		if (nb_user >= limit.get())
		{
			user->setSendCache(ERR_CHANNELISFULL(name.get()));
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
		if ((it->first)->nick_name.get() == nick)
			return it->first;
	}
	return NULL;
}

std::string Channel::getUserList()
{
	t_users_map::iterator	it;
	t_users_map::iterator	ite = _users_map.end();
	std::string	list = "";
	//User * user;
	for ( it = _users_map.begin() ; it != ite ; it++)
	{
		if (it->second != INVITED)
		{
			if (it->second == OPERATOR)
				list.append("@");
			else
				list.append("+");
			//user = *it->first();
			//list.append(user->getNickname());

			list.append(" ");
		}
	}
	return list;
}

