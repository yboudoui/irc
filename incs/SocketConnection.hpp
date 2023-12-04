/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketConnection.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:16:24 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/04 15:34:02 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETREQUEST_HPP
# define SOCKETREQUEST_HPP

# include "Queue.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include <netinet/in.h>

class SocketConnection : public IQueueEventListener
{
	private:
		int					_fd;
		struct sockaddr		_addr;
		socklen_t			_addr_len;
		IQueue				&_queue;
		std::string			_read_cache;
		std::string			_cache;

	public:
		SocketConnection(IQueue &queue, int fd_socketBind);
		~SocketConnection();
		void	read(void);
		void	write(void);
};

#endif
