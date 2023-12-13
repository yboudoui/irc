/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketBind.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/13 18:37:00 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETBIND_HPP
# define SOCKETBIND_HPP

# include "Queue.hpp"
# include "SocketConnection.hpp"
# include "Wagner.hpp"

# include <vector>

class SocketBind : public IQueueEventListener {
	private:
		int								_fd;
		struct sockaddr_in				_sin;
		IQueue							&_queue;
		Wagner &_w;
		~SocketBind();

	public:
		SocketBind(Wagner &w,IQueue &queue, int port, int backlog = 5);
		void	read(void);
		void	write(void);
};

#endif
