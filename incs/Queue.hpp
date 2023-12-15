/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:07:28 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/15 17:40:54 by yboudoui         ###   ########.fr       */
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
# include "IOrchestrator.hpp"
# include "Colors.hpp"

# define MAX_EVENTS 32

# define DEBUG_CALL_QUEUE PRINT_DEBUG_CALL(YELLOW, Queue)

class Queue : public IQueue {
	private:
		int					_epoll_instance;
		struct epoll_event	*_events_list;
		size_t				_max_events;
		IOrchestrator		&_orchestrator;

	public:
		Queue(IOrchestrator& orchestrator, size_t nevents = MAX_EVENTS);
		~Queue();

		void	subscribe(int fd, IQueueEventListener* listener);
		void	unsubscribe(int fd);
		bool	event_loop(void);
};
#endif
