/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/03 16:50:05 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "responses.hpp"

Channel::Channel()
{
	modes = 0;
	DEBUG_CALL_CHANNEL
}

Channel::~Channel()
{
	// FIXSEGFAULT
	//std::string	quit("QUIT :The channel is closed\r\n");
	//sendToAllUsers(quit);
	//for (t_users_map::iterator it = _users_map.begin(); it != _users_map.end(); it++)
	//	remove(it->first);
	DEBUG_CALL_CHANNEL
}


void	Channel::invite(User* user)
{
	std::cout << "invite : " << user->nick_name.get() << std::endl;
	_users_map.insert(std::make_pair(user, INVITED));
	std::cout << "user status :" << _users_map.find(user)->second << std::endl;
}

bool	Channel::join(User* user, std::string usr_password)
{
	if (user == NULL)
		return true;
	std::cout << "JOIN" << std::endl;
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
			std::cout << "convert user status" << std::endl;
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
	t_users_map::iterator	it = _users_map.find(user);
	if (it == _users_map.end())
		return ;
	// FIXSEGFAULT 
	// user->quit(this);
	_users_map.erase(it);
}

std::string	Channel::getChannelModes()
{
	std::string	output;

	if(modes & INVITE_ONLY)
		output.append("i");
	if(modes & TOPIC_ONLY_OP)
		output.append("t");
	if(modes & KEY_PROTECTED)
		output.append("k");
	if(modes & USER_LIMIT)
		output.append("l");
	if (output.size())
		output.insert(0, "+");
	return (output);
}
std::string Channel::getChannelModesParams()
{
	std::string modeparams;
	std::stringstream ss;

	if(modes & KEY_PROTECTED)
		modeparams.append(password() + " ");
	if(modes & USER_LIMIT)
	{
		ss << limit;
		modeparams.append(ss.str());
	}
	return (modeparams);
}
bool		Channel::isOperator(User* user)
{
	t_users_map::iterator	found = _users_map.find(user);
	t_users_map::iterator	end = _users_map.end();

	return ((found != end) && (found->second & OPERATOR));
}

bool		Channel::isInvited(User* user)
{
	t_users_map::iterator	found = _users_map.find(user);
	t_users_map::iterator	end = _users_map.end();

	return ((found != end) && (found->second & INVITED));
}

bool		Channel::isInChannel(User* user)
{
	t_users_map::iterator	it = _users_map.begin();
	t_users_map::iterator	ite = _users_map.end();

	it = _users_map.find(user);
	if (it == ite)
		return false;
	return true;
}

bool	Channel::canJoin(User* user, std::string usr_password)
{
		std::cout << user->nick_name.get() << " can Join ?" << std::endl;
	if (modes & KEY_PROTECTED)
	{
		if (password && usr_password != password())
		{
			user->setSendCache(ERR_BADCHANNELKEY(name));
			return (false);
		}
	}
	if (modes & USER_LIMIT)
	{
		size_t nb_user = countUser();
		if (nb_user >= limit)
		{
			user->setSendCache(ERR_CHANNELISFULL(name));
			return false;
		}
	}
	if (modes & INVITE_ONLY)
	{
		t_users_map::iterator it = _users_map.find(user);
		User * test = findUser(user->nick_name.get());
		if (!test)
		{
			user->setSendCache(ERR_INVITEONLYCHAN(user->nick_name.get(), name));
			return false;
		}
		std::cout << "INVITE_ONLY  >> " << user->nick_name.get() << std::endl;
		std::cout << (it->first)->nick_name.get() << "it->second >> " << it->second << std::endl;
		if (it != _users_map.end() && it->second == INVITED)
			return true;
		else
			user->setSendCache(ERR_INVITEONLYCHAN(user->nick_name.get(), name));
		return false;
	}
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

available<t_client>	Channel::find_by(predicate<User*>& predicate)
{
	available<t_client>		output;
	t_users_map::iterator	it = _users_map.begin();
	t_users_map::iterator	end = _users_map.end();

	for (; it != end; it++)
	{
		if (predicate(it->first))
		{
			output(*it);
			return (output);
		}
	}
	return (output);
}

std::string Channel::getUserList()
{
	t_users_map::iterator	it;
	t_users_map::iterator	ite = _users_map.end();
	std::string	list = "";
	User * user;
	for ( it = _users_map.begin() ; it != ite ; it++)
	{
		if (it->second != INVITED)
		{
			if (it->second == OPERATOR)
				list.append("@");
			//else
			//	list.append("");
			user = it->first;
			list.append(user->nick_name.get());
			
			list.append(" ");
		}
	}
	list.erase(list.size() - 1);
	return list;
}

void	Channel::sendToAllUsers(std::string msg, User* user)
{
	t_users_map::iterator	it;

	for (it = _users_map.begin(); it != _users_map.end(); it++)
	{
		if (it->first == user)
			continue ;
		it->first->setSendCache(msg);
	}
}

void	Channel::sendNameReplyToAllUsers(User* user)
{
	t_users_map::iterator	it;
	std::string msg;

	//(void)user;

	for (it = _users_map.begin(); it != _users_map.end(); it++)
	{
		if (it->first == user)
			continue ;
		msg = RPL_NAMREPLY(it->first->nick_name.get(), this);
		it->first->setSendCache(msg);
		it->first->setSendCache(RPL_ENDOFNAMES(it->first->nick_name.get(), this));

	}
}

User *	Channel::findUser(std::string nickname)
{
	for (t_users_map::iterator it = _users_map.begin(); it != _users_map.end(); it++)
	{
		if (it->first->nick_name.get() == nickname && it->second != INVITED)
			return it->first;
	}
	return NULL;
}

