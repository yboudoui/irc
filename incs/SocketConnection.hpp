/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketConnection.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:16:24 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/08 16:48:46 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETCONNECTION_HPP
# define SOCKETCONNECTION_HPP

# include "Colors.hpp"
# include "Queue.hpp"
# include "Request.hpp"
# include "Wagner.hpp"
# include "User.hpp"
# include <netinet/in.h>

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

		t_message_queue			_requests, _responses;

		Wagner &			_w;
		~SocketConnection();

	public:
		SocketConnection(Wagner &w, IQueue &queue, int fd_socketBind);

		void	read(void);
		void	write(void);

		int const &	getFd() const;
		void	insertResponse(t_message message);
};

#endif
