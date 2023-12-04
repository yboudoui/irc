/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketConnection.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:15:58 by yboudoui          #+#    #+#             */
/*   Updated: 2023/09/24 12:44:51 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketConnection.hpp"
#include <iostream>

SocketConnection::SocketConnection(IQueue &queue, int fd_socketBind) : _queue(queue)
{
	_addr = (struct sockaddr){};
	_addr_len = sizeof(_addr);
	_fd = accept(fd_socketBind, &_addr, &_addr_len);
	if (_fd < 0)
		throw std::runtime_error("Fatal error when accepting a new connection");
	_queue.subscribe(_fd, *this);
	_request = new Request(_fd);
}

SocketConnection::~SocketConnection()
{
	_queue.unsubscribe(_fd);
	close(_fd);
	delete _request;
}

void	SocketConnection::read(void)
{
	t_request	request;

	if (_request->recv(request) == false)
		return ;
	std::cout << request << std::endl;

	Response response = Response();
	response.statusCode(request.header.uri.compare("/") ? 202 : 200);
	response.optinalHeader("lol") = "lol";
	std::string b("<style>h1 { color: blue; font-size: 32px; }</style><h1>Hello, world !</h1>");
	response.body(b);
	_cache = response.str();
}

void	SocketConnection::write(void)
{
	if (_cache.empty())
		return ;
	int	bytes_send = send(_fd, _cache.c_str(), _cache.size(), 0);
	_cache.erase(0, bytes_send);
}
