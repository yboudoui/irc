/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 11:17:03 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Queue.hpp"

bool	Queue::_stop = false;

Queue::Queue(IOrchestrator& orchestrator, size_t max_events)
	: _max_events(max_events)
	, _orchestrator(orchestrator)
{
	_epoll_instance = epoll_create(_max_events);	/* for backward compatibility */
	if (_epoll_instance < 0)
		throw std::runtime_error("Fatal error when creating the monitoring socket instance");
	_events_list = new struct epoll_event [_max_events];
}

void	Queue::subscribe(int fd, IQueue::IEventListener* listener)
{
	DEBUG_CALL_QUEUE

	struct epoll_event ev;

	ev.events	=	EPOLLIN | EPOLLOUT;// | EPOLLET;
	ev.data.ptr	=	listener;
	epoll_ctl(_epoll_instance, EPOLL_CTL_ADD, fd, &ev);
}

void	Queue::unsubscribe(int fd)
{
	DEBUG_CALL_QUEUE

	epoll_ctl(_epoll_instance, EPOLL_CTL_DEL, fd, NULL);
}

bool	Queue::event_loop(void)
{
	int	num_events;

	if (_stop)
		return (false);
	num_events = epoll_wait(_epoll_instance, _events_list, _max_events, 0);
	if (num_events < 0)
	{
		std::cout << "Big error.." << std::endl;
		return (false);
	}
	for (int i = 0; i < num_events; i++)
	{
		IQueue::IEventListener* listener = (IQueue::IEventListener*)_events_list[i].data.ptr;
		if (listener->is_alive() == false)
		{
			IQueue::IEventListener::free(listener);
			continue ;
		}
		if (_events_list[i].events & EPOLLIN)
			listener->read();
		if (_events_list[i].events & EPOLLOUT)
		{
			_orchestrator.treatEventListener(listener);
			listener->write();
		}
	}
	return (true);
}

Queue::~Queue()
{
	DEBUG_CALL_QUEUE
	close(_epoll_instance);
	delete [] _events_list;
}

void	Queue::stop(int sig_value)
{
	(void)sig_value;
	_stop = true;
}

