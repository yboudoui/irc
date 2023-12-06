/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketConnection.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:15:58 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/06 18:46:54 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colors.hpp"
#include "SocketConnection.hpp"
#include "Wagner.hpp"
#include <iostream>

SocketConnection::SocketConnection(Wagner &w, IQueue &queue, int fd_socketBind)
	: _queue(queue)
	, _requestParser(_fd)
	, _w(w)
{
	_addr = (struct sockaddr){};
	_addr_len = sizeof(_addr);
	_fd = accept(fd_socketBind, &_addr, &_addr_len);
	if (_fd < 0)
		throw std::runtime_error("Fatal error when accepting a new connection");
	_queue.subscribe(_fd, *this);
}

SocketConnection::~SocketConnection()
{
	_queue.unsubscribe(_fd);
	close(_fd);
}

void	SocketConnection::read(void)
{
	t_message_queue	tmp;

	tmp = _requestParser.get_messages();
	_requests.insert(_requests.end(), tmp.begin(), tmp.end());
}

void	SocketConnection::write(void)
{
	std::stringstream	stream;
	t_message_queue		tmp;

	tmp = _w.treatRequest(*this, _requests);
	_responses.insert(_responses.end(), tmp.begin(), tmp.end());

	if (_write_cache.empty())
	{
		while (!_responses.empty())
		{
			stream << _responses.front() << "\r\n";
			_responses.pop_front();
		}
		_write_cache = stream.str();
	}
	int	bytes_send = send(_fd, _write_cache.c_str(), _write_cache.size(), 0);
	_write_cache.erase(0, bytes_send);
}
