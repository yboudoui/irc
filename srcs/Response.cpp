/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:33:23 by yboudoui          #+#    #+#             */
/*   Updated: 2023/09/23 14:08:09 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"
#include <sstream>

Response::Response(void)
{
	if (!_status_message_map.empty())
		return ;
	_status_message_map["200"] = "OK";
	_status_message_map["202"] = "Accepted";
}

Response::~Response(void) {}

void	Response::statusCode(int status_code)
{
	std::stringstream temp; temp << status_code;
	_response.header.status_code = temp.str();
}

std::string	&Response::optinalHeader(std::string name)
{
	return _response.header.optional[name];
}

void	Response::body(std::string body)
{
	std::stringstream temp; temp << body.size();
	_response.body = body;
	_response.header.optional["Content-Length"]  = temp.str();
}

std::string	Response::str(void) const
{
	std::ostringstream									os;
	std::map<std::string, std::string>::const_iterator	it;

	if (_response.header.status_code.empty())
		return (os.str());
	os << HTTP_VERSION << " ";
	os << _response.header.status_code << " ";
	os << _status_message_map[_response.header.status_code] << "\r\n";
	for (it = _response.header.optional.begin(); it != _response.header.optional.end(); it++)
		os << it->first << ": " << it->second << "\r\n";
	if (!_response.body.empty())
		os << "\r\n" << _response.body << "\r\n";
	return (os.str());
}

std::ostream& operator<<(std::ostream& stream, const Response &r)
{
	stream << r.str();
	return (stream);
}

# define BLUE "\033[1;34m"
# define GREEN "\033[1;32m"
# define PURPLE "\033[1;35m"
# define RESET "\033[0m"

std::ostream& operator<< (std::ostream& stream, const t_response &response)
{
	stream << "\t" << GREEN << HTTP_VERSION;
	stream << "\t" << PURPLE << response.header.status_code;
	stream << "\t" << RESET << _status_message_map[response.header.status_code] << std::endl;

	std::map<std::string, std::string>::const_iterator it;
	for (it = response.header.optional.begin(); it != response.header.optional.end(); it++)
		stream << "\t" << GREEN << it->first << RESET << ":" << it->second << std::endl;
	stream << "\t" << GREEN << response.body << RESET << std::endl;
	return stream;
}
