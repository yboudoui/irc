/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:08:10 by yboudoui          #+#    #+#             */
/*   Updated: 2023/09/22 15:01:23 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	if (_request == NULL)
		_request = new t_request;

	std::string	line;
	while (getNextLine(line))
	{
		if (line.size() == 0)
		{
			_cache.clear();
			request = (*_request);
			delete _request;
			_request = NULL;
			return (true);
		}
		if (!parseHeader(line))
			parseOptionalHeader(line);
	}
	return (false);
}

bool	Request::getNextLine(std::string &line)
{
	line.clear();
	std::size_t	endl = _cache.find("\r\n");
	if (endl == std::string::npos)
		return (false);
	line = _cache.substr(0, endl);
	_cache.erase(0, endl + 2);
	return (true);
}

bool	Request::parseHeader(std::string line)
{
	std::size_t	position;

	if (!_request->header.method.empty())
		return (false);
	position = line.find(" ");
	_request->header.method = line.substr(0, position);
	line.erase(0, position + 1);
	position = line.find(" ");
	_request->header.uri = line.substr(0, position);
	line.erase(0, position + 1);
	position = line.find(" ");
	_request->header.version = line.substr(0, position);
	return (true);
}

void	Request::parseOptionalHeader(std::string line)
{
	std::size_t	colomn = line.find(":");
	if (colomn != std::string::npos)
		_request->header.optional[line.substr(0, colomn)] = line.substr(colomn + 1);
}

# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define RESET "\033[0m"

std::ostream& operator<< (std::ostream& stream, const t_request& request)
{
	stream << "\t" << BLUE << request.header.method;
	stream << "\t" << PURPLE << request.header.uri;
	stream << "\t" << RESET << request.header.version << std::endl;

	std::map<std::string, std::string>::const_iterator it;
	for (it = request.header.optional.begin(); it != request.header.optional.end(); it++)
		stream << "\t" << BLUE << it->first << RESET << ":" << it->second << std::endl;
	return stream;
}
