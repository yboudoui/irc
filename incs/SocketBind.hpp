/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketBind.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/03 13:40:01 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETBIND_HPP
# define SOCKETBIND_HPP

# include "IOrchestrator.hpp"
# include "SocketConnection.hpp"
# include <stdexcept>
# include <unistd.h>

# include "Colors.hpp"
# define DEBUG_CALL_SOCKET_BIND_CONSTRUCTOR \
	PRINT_DEBUG_CALL_MESSAGE(BOLD << CYAN, "", SocketBind, "\n")

# define DEBUG_CALL_SOCKET_BIND_DESTRUCTOR \
	PRINT_DEBUG_CALL_MESSAGE(BOLD << CYAN, "", SocketBind, RESET << " -> ")

class SocketBind : public IQueue::IEventListener {
	private:
		int								_fd;
		struct sockaddr_in				_sin;
		IQueue							&_queue;
		IOrchestrator					&_orchestrator;

	public:
		SocketBind(IOrchestrator &orchestrator, IQueue &queue, int port, int backlog = 5);
		~SocketBind();
		void	read(void);
		void	write(void);
};

#endif
