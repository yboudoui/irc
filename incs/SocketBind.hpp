/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketBind.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/04 11:39:24 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETBIND_HPP
# define SOCKETBIND_HPP

# include "Queue.hpp"
# include "SocketConnection.hpp"

# include <vector>

class SocketBind : public IQueueEventListener {
	private:
		int								_fd;
		struct sockaddr_in				_sin;
		IQueue							&_queue;
		std::vector<SocketConnection*>	_v;

	public:
		SocketBind(IQueue &queue, int port, int backlog = 5);
		~SocketBind();
		void	read(void);
		void	write(void);
};

#endif
