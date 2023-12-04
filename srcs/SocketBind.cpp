/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketBind.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:07 by yboudoui          #+#    #+#             */
/*   Updated: 2023/09/17 18:25:14 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketBind.hpp"

SocketBind::SocketBind(IQueue &queue, int port, int backlog) : _queue(queue)
{
	_fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if (_fd < 0)
		throw std::runtime_error("Fatal error when creating a new socket");
	_sin.sin_family			= AF_INET;
	_sin.sin_port			= htons(port);
	_sin.sin_addr.s_addr	= htonl(INADDR_ANY);
	if (::bind(_fd, (struct sockaddr *)&_sin, sizeof (_sin)) < 0)
		throw std::runtime_error("Fatal error when binding the new socket");
	if (::listen(_fd, backlog) < 0)
		throw std::runtime_error("Fatal error when listening the new socket");
	_queue.subscribe(_fd, *this);
}

SocketBind::~SocketBind()
{
	_queue.unsubscribe(_fd);
	close(_fd);
}

void	SocketBind::read(void)
{
	SocketConnection	*new_connection = new SocketConnection(_queue, _fd);
	_v.push_back(new_connection);
}

void	SocketBind::write(void) {}
