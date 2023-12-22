/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/22 14:08:09 by yboudoui         ###   ########.fr       */
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

void	User::setUsername		(std::string name){	_username = name; }
void	User::setHostname		(std::string name){	_hostname = name; }
void	User::setServername		(std::string name){	_servername = name; }
void	User::setRealname		(std::string name){	_realname = name; }
void	User::setNickname		(std::string name){	_nickname = name; }

std::string const &	User::getUsername		(void) const{ return _username; }
std::string const &	User::getHostname		(void) const{ return _hostname; }
std::string const &	User::getServername		(void) const{ return _servername; }
std::string const &	User::getRealname		(void) const{ return _realname; }
std::string const &	User::getNickname		(void) const{ return _nickname; }

bool	User::isConnected() const
{
	if (!this->_connection_complete)
	{
		return true;
	}
	return false;
}

void	User::connectionStep()
{
	if (this->_connection_complete)
		this->_connection_complete--;
}
