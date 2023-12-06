/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketConnection.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:16:24 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/06 18:47:29 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SocketConnection_HPP
# define SocketConnection_HPP

# include "Queue.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "Wagner.hpp"
# include <netinet/in.h>
# include <vector>

class Wagner;
class SocketConnection : public IQueueEventListener
{
	private:
		int						_fd;
		struct sockaddr			_addr;
		socklen_t				_addr_len;
		IQueue					&_queue;
		std::string				_read_cache;
		std::string				_write_cache;
		Request					_requestParser;
		t_message_queue			_requests;
		t_message_queue			_responses;
		Wagner &_w;

	public:
		SocketConnection(Wagner &w, IQueue &queue, int fd_socketBind);
		~SocketConnection();

		void	read(void);
		void	write(void);
};

#endif
