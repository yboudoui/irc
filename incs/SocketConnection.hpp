/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketConnection.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:16:24 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/08 17:02:29 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETCONNECTION_HPP
# define SOCKETCONNECTION_HPP

# include "Colors.hpp"
# include "Queue.hpp"
# include "Message.hpp"
# include "Request.hpp"
# include "Wagner.hpp"
# include "User.hpp"
# include <netinet/in.h>

class Wagner;
class Request;

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

		t_message_reponse_queue			_responses;
	
		std::string			_username;
		std::string			_hostname;
		std::string			_servername;
		std::string			_realname;

		std::string			_nickname;

		Wagner &			_w;
		~SocketConnection();

	public:
		SocketConnection(Wagner &w, IQueue &queue, int fd_socketBind);

		void	read(void);
		void	write(void);

		int const &	getFd() const;

		void	insertResponse(MessageResponse message);
};

#endif
