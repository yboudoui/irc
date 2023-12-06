/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserSocket.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:16:24 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/06 12:38:27 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERSOCKET_HPP
# define USERSOCKET_HPP

# include "Queue.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include <netinet/in.h>
# include <vector>

class UserSocket : public IQueueEventListener
{
	private:
		int						_fd;
		struct sockaddr			_addr;
		socklen_t				_addr_len;
		IQueue					&_queue;
		std::string				_read_cache;
		std::string				_write_cache;
		Request					_requestParser;
		t_request_queue			_requests;

		std::vector<t_response*> _responses;
	
		std::string			_username;
		std::string			_hostname;
		std::string			_servername;
		std::string			_realname;

		std::string			_nickname;
		//std::vector<Channel&>	_channels;

	public:
		UserSocket(IQueue &queue, int fd_socketBind);
		~UserSocket();

		void	read(void);
		void	write(void);
		
		std::string const &	getResponse() const;
};

#endif
