/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketConnection.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:16:24 by yboudoui          #+#    #+#             */
/*   Updated: 2023/09/23 14:20:18 by yboudoui         ###   ########.fr       */
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
		Request				*_request;
		std::string			_cache;

	public:
		SocketConnection(IQueue &queue, int fd_socketBind);
		~SocketConnection();
		void	read(void);
		void	write(void);
};

#endif
