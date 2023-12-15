/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketBind.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/15 18:11:56 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETBIND_HPP
# define SOCKETBIND_HPP

# include "IOrchestrator.hpp"
# include "SocketConnection.hpp"
# include <stdexcept>
# include <unistd.h>

class SocketBind : public IQueueEventListener {
	private:
		int								_fd;
		struct sockaddr_in				_sin;
		IQueue							&_queue;
		IOrchestrator					&_orchestrator;
		~SocketBind();

	public:
		SocketBind(IOrchestrator &orchestrator, IQueue &queue, int port, int backlog = 5);
		void	read(void);
		void	write(void);
};

#endif
