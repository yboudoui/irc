/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketConnection.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:15:58 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/11 18:38:13 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketConnection.hpp"

SocketConnection::SocketConnection(Wagner &w, IQueue &queue, int fd_socketBind)
	: _queue(queue)
	, _w(w)
{
	_addr = (struct sockaddr){};
	_addr_len = sizeof(_addr);
	_fd = accept(fd_socketBind, &_addr, &_addr_len);
	if (_fd < 0)
		throw std::runtime_error("Fatal error when accepting a new connection");
	_queue.subscribe(_fd, this);
}

SocketConnection::~SocketConnection()
{
	_queue.unsubscribe(_fd);
	close(_fd);
}

void	SocketConnection::read(void)
{
	size_t					bytes_read = 0;
	const unsigned int		buff_len = 512;
	char					buff[buff_len] = {0};

	bytes_read = ::recv(_fd, buff, buff_len, 0);
	_read_cache.append(buff, bytes_read);
	_requests >> _read_cache;
}

int const &	SocketConnection::getFd() const
{
	return(_fd);
}

void	SocketConnection::insertResponse(Message message)
{
	_responses.push_back(new Message(message));
}

void	SocketConnection::write(void)
{
	try
	{
		_write_cache << _responses << _w.treatRequest(this, _requests);
		int	bytes_send = send(_fd, _write_cache.c_str(), _write_cache.size(), 0);
		_write_cache.erase(0, bytes_send);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
