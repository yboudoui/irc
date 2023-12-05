/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketBind.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/05 15:49:30 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETBIND_HPP
# define SOCKETBIND_HPP

# include "Queue.hpp"
# include "UserSocket.hpp"
# include "Wagner.hpp"

# include <vector>

class SocketBind : public IQueueEventListener {
	private:
		int								_fd;
		struct sockaddr_in				_sin;
		IQueue							&_queue;
		Wagner &_w;

	public:
		SocketBind(Wagner &w,IQueue &queue, int port, int backlog = 5);
		~SocketBind();
		void	read(void);
		void	write(void);
};

#endif
