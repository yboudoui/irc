/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:08:10 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/04 15:23:03 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colors.hpp"
#include "Request.hpp"

#include <iostream>

Request::Request(int fd): _fd(fd), _request(NULL) {}

Request::~Request(void) {}

bool	Request::recv(t_request &request)
{
	size_t				bytes_read = 0;
	const unsigned int	buff_len = 512;
	char				buff[buff_len] = {0};

	request = (t_request){};
	bytes_read = ::recv(_fd, buff, buff_len, 0);
	_cache.append(buff, bytes_read);
	std::cout << "cache >> " << BLUE << _cache <<  RESET << std::endl;


	if (_request == NULL)
		_request = new t_request;

	std::size_t	endl = _cache.find("\r\n");
	if (endl == std::string::npos)
		return (false);

	/* message complet */
	/* on conserve l eventuel message suivant dans _cache */
	std::string line = _cache.substr(0, endl);
	_cache.erase(0, endl + 2);
	
	std::cout << ">> " << line << std::endl;
	std::cout << "EOM(2)" << std::endl;
	/* 
	TODO 
	>> enregistrer le message (function REGEXP ) dans s_request
	>> creer la reponse (dans SocketConnection::read())*/
	return (true);
}
