/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketConnection.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:16:24 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/28 13:19:11 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETCONNECTION_HPP
# define SOCKETCONNECTION_HPP

# include <netinet/in.h>
# include <string>
# include "IQueue.hpp"
# include <stdexcept>
# include <unistd.h>

# define BUFFER_LEN	512

# include "Colors.hpp"
# define DEBUG_CALL_SOCKET_CONNECTION \
	PRINT_DEBUG_CALL_MESSAGE(CYAN, SocketConnection, "")

class SocketConnection : public IQueue::IEventListener
{
	private:
		int						_fd;
		struct sockaddr			_addr;
		socklen_t				_addr_len;
		char					_buffer[BUFFER_LEN];

		IQueue					&_queue;

		std::string				_read_cache, _write_cache;

	protected:
		~SocketConnection();

	public:
		SocketConnection(IQueue &queue, int fd_socketBind);

		void			read(void);
		void			write(void);
		void			setSendCache(std::string message);
		std::string&	getReadCache(void);
};

#endif
