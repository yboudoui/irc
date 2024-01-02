/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketConnection.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:15:58 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/02 16:22:54 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketConnection.hpp"

SocketConnection::SocketConnection(IQueue &queue, int fd_socketBind)
	: _queue(queue)
{
	_addr = (struct sockaddr){};
	_addr_len = sizeof(_addr);
	_fd = accept(fd_socketBind, &_addr, &_addr_len);
	if (_fd < 0)
		throw std::runtime_error("Fatal error when accepting a new connection");
	_queue.subscribe(_fd, this);
	DEBUG_CALL_SOCKET_CONNECTION_CONSTRUCTOR
}

SocketConnection::~SocketConnection()
{
	DEBUG_CALL_SOCKET_CONNECTION_DESTRUCTOR
	_queue.unsubscribe(_fd);
	close(_fd);
}

void	SocketConnection::read(void)
{
	ssize_t bytes_read = ::recv(_fd, _buffer, BUFFER_LEN, 0);
	_read_cache.append(_buffer, bytes_read);
}

void	SocketConnection::setSendCache(std::string message)
{
	if (message.empty())
		return ;
	_write_cache.append(message);
}

std::string&	SocketConnection::getReadCache(void)
{
	return (_read_cache);
}

void	SocketConnection::write(void)
{
	ssize_t	bytes_send;
	bytes_send = ::send(_fd, _write_cache.c_str(), _write_cache.size(), 0);
	_write_cache.erase(0, bytes_send);
}
