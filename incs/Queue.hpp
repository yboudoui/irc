/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:07:28 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/08 16:51:03 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP

extern "C" {
# include <sys/epoll.h>
}

# include <unistd.h>

# include <map>
# include <stdexcept>
# include "Colors.hpp"

# define MAX_EVENTS 32

# define DEBUG_CALL_QUEUE PRINT_DEBUG_CALL(YELLOW, Queue)

class IQueueEventListener
{
	public:
		IQueueEventListener(void);
		bool			is_alive(bool alive = true);
		virtual void	read(void)	= 0;
		virtual void	write(void)	= 0;
		static void free(IQueueEventListener* p) { delete p; };
	protected:
		virtual	~IQueueEventListener(void) = 0;
	private:
		bool	_alive;
};

class IQueue {
	public:
		virtual void	subscribe(int fd, IQueueEventListener* event)	= 0;
		virtual void	unsubscribe(int fd)	= 0;
};

class Queue : public IQueue {
	private:
		int					_epoll_instance;
		struct epoll_event	*_events_list;
		size_t				_max_events;

	public:
		Queue(size_t nevents = MAX_EVENTS);
		~Queue();

		void	subscribe(int fd, IQueueEventListener* listener);
		void	unsubscribe(int fd);
		bool	event_loop(void);
};
#endif
