/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketBind.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:07 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/02 17:43:51 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketBind.hpp"

SocketBind::SocketBind(IOrchestrator& orchestrator, IQueue &queue, int port, int backlog)
	: _queue(queue)
	, _orchestrator(orchestrator)
{
	_fd = ::socket(AF_INET, SOCK_STREAM /*| SOCK_NONBLOCK */, 0);
	if (_fd < 0)
		throw std::runtime_error("Fatal error when creating a new socket");
	_sin.sin_family			= AF_INET;
	_sin.sin_port			= htons(port);
	_sin.sin_addr.s_addr	= htonl(INADDR_ANY);
	if (::bind(_fd, (struct sockaddr *)&_sin, sizeof (_sin)) < 0)
		throw std::runtime_error("Fatal error when binding the new socket");
	if (::listen(_fd, backlog) < 0)
		throw std::runtime_error("Fatal error when listening the new socket");
	_queue.subscribe(_fd, this);
	DEBUG_CALL_SOCKET_BIND_CONSTRUCTOR
}

SocketBind::~SocketBind()
{
	DEBUG_CALL_SOCKET_BIND_DESTRUCTOR
	_queue.unsubscribe(_fd);
	close(_fd);
}

void	SocketBind::read(void)
{
	_orchestrator.addEventListener(_queue, _fd);
}

void	SocketBind::write(void) {}
