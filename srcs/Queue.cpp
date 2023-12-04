/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/04 11:37:49 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Queue.hpp"

Queue::Queue(size_t max_events) : _max_events(max_events) {
	_epoll_instance = epoll_create(_max_events);	/* for backward compatibility */
	if (_epoll_instance < 0)
		throw std::runtime_error("Fatal error when creating the monitoring socket instance");
	_events_list = new struct epoll_event [_max_events];
}

void	Queue::subscribe(int fd, IQueueEventListener &listener) {
	struct epoll_event ev;
	ev.events	=	EPOLLIN | EPOLLOUT;
	ev.data.fd	=	fd;
	epoll_ctl(_epoll_instance, EPOLL_CTL_ADD, fd, &ev);
	_m.insert(std::pair<int, IQueueEventListener&>(fd, listener));
}

void	Queue::unsubscribe(int fd) {
	epoll_ctl(_epoll_instance, EPOLL_CTL_DEL, fd, NULL);
	_m.erase(fd);
}

bool	Queue::event_loop(void) {
	int							num_events;
	t_listener_map::iterator	listener;

	num_events = epoll_wait(_epoll_instance, _events_list, _max_events, 0);
	if (num_events < 0)
		return (false);
	for (int i = 0; i < num_events; i++)
	{
		listener = _m.find(_events_list[i].data.fd);
		if (listener == _m.end())
			continue ;	/* this should never happend */
/*
		if (_events_list[i].events & EV_EOF)
		{
			std::cout << "EOF" << std::endl;
			unsubscribe(_events_list[i].ident);
			continue ;
		}
*/
		if (_events_list[i].events & EPOLLIN)
			listener->second.read();
		if (_events_list[i].events & EPOLLOUT)
			listener->second.write();
	}
	return (true);
}

Queue::~Queue() {
	close(_epoll_instance);
	delete [] _events_list;
}


