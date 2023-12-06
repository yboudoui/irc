/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketConnection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:15:58 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/06 12:58:01 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colors.hpp"
#include "SocketConnection.hpp"
#include "Wagner.hpp"
#include <iostream>

SocketConnection::SocketConnection(Wagner &w, IQueue &queue, int fd_socketBind) : _queue(queue), _requestParser(_fd), _w(w)
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
	t_request_queue	tmp = _requestParser.get_requests();
	_requests.insert(_requests.end(), tmp.begin(), tmp.end());

	_w.treatRequest(*this, _requests);
}

void	SocketConnection::write(void)
{
	std::map<std::string, std::string>	responses;

	responses["PRIVMSG"] = "privmsg";
	responses["JOIN"] = "joined";
	responses["QUIT"] = "quit";
	responses["WHOIS"] = "sethomas sethomas localhost * :Selen Thomas";
	responses["PING"] = "PONG localhost";
	responses["USER"] = ":localhost 001 sethomas :Yeah !";
	responses["CAP"] = "cap";
	responses["NICK"] = "nick";
	responses["MODE"] = "mode";

	// Attention : effacer la requete meme si la reponse est vide :)
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
