/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketConnection.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:15:58 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/04 17:06:56 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colors.hpp"
#include "SocketConnection.hpp"
#include <iostream>

SocketConnection::SocketConnection(IQueue &queue, int fd_socketBind) : _queue(queue)
{
	_addr = (struct sockaddr){};
	_addr_len = sizeof(_addr);
	_fd = accept(fd_socketBind, &_addr, &_addr_len);
	if (_fd < 0)
		throw std::runtime_error("Fatal error when accepting a new connection");
	_queue.subscribe(_fd, *this);
}

SocketConnection::~SocketConnection()
{
	_queue.unsubscribe(_fd);
	close(_fd);
}

void	SocketConnection::read(void)
{
	/*
	concat received mssg 
	*/
	size_t				bytes_read = 0;
	const unsigned int	buff_len = 512;
	char				buff[buff_len] = {0};

	bytes_read = ::recv(_fd, buff, buff_len, 0);
	_read_cache.append(buff, bytes_read);
	std::cout << "_read_cache >> " << BLUE << _read_cache <<  RESET << std::endl;

/*
	t_request	request;

	if (_request->recv(request) == false)
		return ;


	std::cout << "response :" << std::endl;
	Response response = Response();
	response.statusCode(request.header.uri.compare("/") ? 202 : 200);
	response.optinalHeader("lol") = "lol";
	std::string b("<style>h1 { color: blue; font-size: 32px; }</style><h1>Hello, world !</h1>");
	response.body(b);
	_cache = response.str();
	std::cout << _cache << std::endl;
*/
}

void	SocketConnection::write(void)
{
	if (_cache.empty())
	{
		std::size_t	endl = _read_cache.find("\r\n");
		while (endl != std::string::npos)
		{
			std::string line = _read_cache.substr(0, endl);
			std::size_t	whois = line.find("WHOIS");
			std::size_t	user = line.find("USER");
			if (whois != std::string::npos)
			{
				_cache = ":localhost 311 sethomas sethomas localhost :sethomas\r\n"; // response
			}
			else if (user != std::string::npos)
			{
				_cache = ":localhost 001 sethomas :Yeah !\r\n"; // response
			}
			_read_cache.erase(0, endl + 2);
			
			std::cout << GREEN << "<< " << line << RESET << std::endl;
			std::cout << GREEN << ">> " << _cache << RESET << std::endl;
			endl = _read_cache.find("\r\n");
		}
	}
	//_cache = ":localhost 001 sethomas :Yeah !\r\n"; // response


	/* message complet */
	/* on conserve l eventuel message suivant dans _cache */


	int	bytes_send = send(_fd, _cache.c_str(), _cache.size(), 0);
	_cache.erase(0, bytes_send);
}
