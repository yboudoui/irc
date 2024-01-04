/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 11:56:16 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User*	User::_debug = NULL;

User::User(IQueue &queue, int fd)
	: SocketConnection(queue, fd)
	, _connection_complete(2)
{
	DEBUG_CALL_USER
}

User::~User()
{
	quitAllChannels();
	DEBUG_CALL_USER_DESTRUCTOR
}

bool	User::isConnected() const
{
	return (_connection_complete == 0);
}

void	User::connectionStep()
{
	if (_connection_complete)
		_connection_complete--;

	if (_connection_complete != 0)
		return ;
	send_message(RPL_WELCOME(this)); //001
	send_message(RPL_YOURHOST()); //002
	send_message(RPL_CREATED()); //003
	send_message(RPL_MYINFO()); //004
}

void	User::join(Channel* channel)
{
	if (channel == NULL)
		return ;
	_channels.insert(std::make_pair(channel->name, channel));
}

void	User::quitAllChannels(void)
{
	if (_channels.size())
	{
		t_channels::iterator it;
		t_channels::iterator ite = _channels.end();
		for (it = _channels.begin(); it != ite; it++)
		{
			if (it->second)
				it->second->remove(this);
		}
	}
}

void	User::quit(Channel* channel)
{
	if (channel == NULL)
		return ;
	_channels.erase(channel->name);
	channel->remove(this);
}

void	User::sendToAllChannels(std::string message)
{
	t_channels::iterator it = _channels.begin();

	std::string privmsg;

	for (; it != _channels.end(); it++)
	{	
		privmsg = PRIVMSG(nick_name, it->second->name, message);
		it->second->send(nick_name, privmsg);
	}
}

bool	User::send(std::string channelName, std::string message)
{
	t_channels::iterator	it;

	it = _channels.find(channelName);
	if (it != _channels.end())
		return (it->second->send(nick_name, message), true);
	return (false);
}

void	User::sendTo(Channel* channel, std::string msg)
{
	if (channel == NULL)
		return ;
	if (_channels.find(channel->name) != _channels.end())
		channel->sendToAllUsers(msg, this);
}

void	User::debug(User* u)
{
	if (u == NULL)
		return ;
	_debug = u;
	PRINT_MESSAGE(WHITE, BOLD << "[" << u->getFD() << "]["<< u->nick_name<< "]\t", "", "\n");
}

bool	User::read_message(Message** msg)
{
	return (is_alive() && new_message(getReadCache(), msg));
}

void	User::send_message(std::string msg)
{
	static size_t	number_send = 0;
	if (this != _debug)
		number_send += 1;
	if (this == _debug)
	{
		PRINT_MESSAGE(GREEN, "\t", msg, "\b\b");
		if (number_send != 0)
		{
			PRINT_MESSAGE(WHITE, "\t" << number_send << " message was sent to other users", "", "\n");
			number_send = 0;
		}
	}
	setSendCache(msg);
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
				return (input && input->nick_name == _nick_name);
			}
	}	predicate;
	return (predicate);
}
