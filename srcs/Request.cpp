/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:08:10 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/05 14:12:56 by yboudoui         ###   ########.fr       */
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

t_request	Request::parse_request(std::string str) {
	t_request	output;

	output.prefixe = parse_prefixe(&str);
}

static std::string	*extract_from(std::string &str, const char *delimiter) {
	std::size_t	has_delimiter = str.find(delimiter);
	if (has_delimiter == std::string::npos)
		return (NULL);
	std::string	*output = new std::string(str, has_delimiter);
	str.erase(has_delimiter);
}

t_prefixe*	Request::parse_prefixe(std::string &str) {
	if (str.size() < 2 || str[0] != ':')
		return (NULL);
	if (str[1] == ' ')
		throw std::runtime_error("Bad prefix format");
	std::size_t	end = str.find(" ", 1);
	std::string substr(str, 1, end);
	str.erase(0, end);
	t_prefixe	*output = new t_prefixe;
	output->host = extract_from(substr, "@");
	output->user = extract_from(substr, "!");
	if (output->host || output->user)
		output->pseudo = extract_from(substr, " ");
	else
		output->server_name = extract_from(substr, " ");
	return (output);
}
