/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserSocket.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:15:58 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/05 12:15:17 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colors.hpp"
#include "UserSocket.hpp"
#include <iostream>

UserSocket::UserSocket(IQueue &queue, int fd_socketBind) : _queue(queue)
{
	_addr = (struct sockaddr){};
	_addr_len = sizeof(_addr);
	_fd = accept(fd_socketBind, &_addr, &_addr_len);
	if (_fd < 0)
		throw std::runtime_error("Fatal error when accepting a new connection");
	_queue.subscribe(_fd, *this);
}

UserSocket::~UserSocket()
{
	_queue.unsubscribe(_fd);
	close(_fd);
}

void	UserSocket::read(void)
{
	/* concat received mssg */
	size_t				bytes_read = 0;
	const unsigned int	buff_len = 512;
	char				buff[buff_len] = {0};

	bytes_read = ::recv(_fd, buff, buff_len, 0);
	if (!bytes_read)
		return ;
	_read_cache.append(buff, bytes_read);
	std::cout << CYAN 
		<< "READ [" << _fd << "] " << std::endl
		<< "-------------" << std::endl
		<< _read_cache 
		<<  RESET << std::endl;
}

void	UserSocket::write(void)
{
	if (_cache.empty())
	{
		std::size_t	endl = _read_cache.find("\r\n");
		while (endl != std::string::npos)
		{
			std::string line = _read_cache.substr(0, endl);
			//std::size_t	privmsg = line.find("PRIVMSG"); //PRIVMSG #channel :msg
			//std::size_t	join = line.find("JOIN"); //JOIN #channel
			//std::size_t	quit = line.find("QUIT"); //QUIT :leaving
	
			std::size_t	whois = line.find("WHOIS");
			std::size_t	user = line.find("USER");
			std::size_t	ping = line.find("PING");

			_cache = "";
			if (whois != std::string::npos)
			{
				//_cache = "sethomas sethomas localhost * :Selen Thomas\r\n"; // response
				//https://datatracker.ietf.org/doc/html/rfc1459#section-6.2
			}
			else if (user != std::string::npos)
			{
				_cache = ":localhost 001 sethomas :Yeah !\r\n"; // response
			}
			else if (ping != std::string::npos)
			{
				_cache = "PONG localhost\r\n";
				// https://datatracker.ietf.org/doc/html/rfc1459#section-4.6.3
			}
			
			
			//JOIN #ff
			
			_read_cache.erase(0, endl + 2);
			
			std::cout << BLUE << "<< [" << _fd << "]" << line << RESET << std::endl;
			std::cout << GREEN << ">> [" << _fd << "]" << _cache << RESET << std::endl;
			endl = _read_cache.find("\r\n");
		}
	}
	//_cache = ":localhost 001 sethomas :Yeah !\r\n"; // response


	/* 
		std::vector<t_response*> _responses;
		std::string const &	getResponse() const;
	*/
	int	bytes_send = send(_fd, _cache.c_str(), _cache.size(), 0);
	_cache.erase(0, bytes_send);
}
