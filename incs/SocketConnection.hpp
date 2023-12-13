/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketConnection.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:16:24 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/13 19:20:34 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETCONNECTION_HPP
# define SOCKETCONNECTION_HPP

# include "Queue.hpp"
# include "Message.hpp"
# include "Wagner.hpp"

# include <netinet/in.h>
# include <cerrno>

class Wagner;

class SocketConnection : public IQueueEventListener
{
	private:
		int						_fd;
		struct sockaddr			_addr;
		socklen_t				_addr_len;

		IQueue					&_queue;

		std::string				_read_cache, _write_cache;
		t_message_queue			_requests, _responses;

		Wagner &			_w;
		~SocketConnection();

	public:
		SocketConnection(Wagner &w, IQueue &queue, int fd_socketBind);

		void	read(void);
		void	write(void);

		void	insertResponse(Message *message);
};

#endif
