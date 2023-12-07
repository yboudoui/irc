/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketConnection.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:16:24 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/07 17:05:36 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETCONNECTION_HPP
# define SOCKETCONNECTION_HPP

# include "Queue.hpp"
# include "Request.hpp"
# include "Wagner.hpp"
# include "User.hpp"
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
	
		std::string			_username;
		std::string			_hostname;
		std::string			_servername;
		std::string			_realname;

		std::string			_nickname;

		Wagner &			_w;
		//std::vector<Channel&>	_channels;

	public:
		SocketConnection(Wagner &w, IQueue &queue, int fd_socketBind);
		virtual ~SocketConnection();

		void	read(void);
		void	write(void);
		
		std::string const &	getResponse() const;
		int const &	getFd() const;

		void	insertResponse(t_message message);
};

#endif
