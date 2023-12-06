/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserSocket.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:15:58 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/06 12:39:25 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colors.hpp"
#include "UserSocket.hpp"
#include <iostream>

UserSocket::UserSocket(IQueue &queue, int fd_socketBind) : _queue(queue), _requestParser(_fd)
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
	t_request_queue	tmp = _requestParser.get_requests();
	_requests.insert(_requests.end(), tmp.begin(), tmp.end());
}

void	UserSocket::write(void)
{
	std::map<std::string, std::string>	responses;

	responses["PRIVMSG"] = "";
	responses["JOIN"] = "";
	responses["QUIT"] = "";
	responses["WHOIS"] = "sethomas sethomas localhost * :Selen Thomas";
	responses["PING"] = "PONG localhost";
	responses["USER"] = ":localhost 001 sethomas :Yeah !";
	responses["CAP"] = "";
	responses["NICK"] = "";

	if (_write_cache.empty())
	{
		for (size_t idx = 0; idx < _requests.size(); idx += 1)
		{
			_write_cache = responses[_requests[idx].command.command];
			if (_write_cache.empty())
				continue ;
	#ifdef DEBUG
			std::cout << GREEN << ">> [" << _fd << "] " << _requests[idx] << RESET << std::endl;
			std::cout << BLUE << "<< [" << _fd << "] " << _write_cache << RESET << std::endl;
	#endif
			_requests.erase(_requests.begin() + idx);
			_write_cache += "\r\n";
		}
	}
	int	bytes_send = send(_fd, _write_cache.c_str(), _write_cache.size(), 0);
	_write_cache.erase(0, bytes_send);
}

void	UserSocket::pong(void)
{
	_response.append("PONG localhots\r\n");
}

void	UserSocket::whois(void)
{
	_response.append("sethomas sethomas localhost :Selen THOMAS\r\n");
}