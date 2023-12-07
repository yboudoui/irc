/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:08:10 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/07 16:02:25 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

#include <iostream>

Request::Request(int &fd): _fd(fd) {}

Request::~Request(void) {}

t_message_queue	Request::get_messages(void)
{
	t_message_queue			output;
	t_message				new_request;
	size_t					bytes_read = 0;
	const unsigned int		buff_len = 512;
	char					buff[buff_len] = {0};

	bytes_read = ::recv(_fd, buff, buff_len, 0);
	_cache.append(buff, bytes_read);

	Extractor	*line = _cache.extract_to("\r\n");
	while (line != NULL)
	{
		new_request.valide = true;
		new_request.prefixe = parse_prefixe(*line);
		new_request.command = parse_command(*line);
		new_request.params = parse_params(*line);
		output.push_back(new_request);
		line = _cache.extract_to("\r\n");
	}
	return (output);
}

t_prefixe*	Request::parse_prefixe(Extractor &str)
{
	if (str.size() < 2 || str[0] != ':')
		return (NULL);
	if (str[1] == ' ')
		throw std::runtime_error("Bad prefix format");
	str.erase(0, 1);
	Extractor *substr = str.extract_to(" ");
	t_prefixe	*output = new t_prefixe;
	output->host = substr->extract_from("@");
	output->user = substr->extract_from("!");
	output->pseudo = (output->host || output->user) ? substr : NULL;
	output->server_name = (output->pseudo == NULL) ? substr : NULL;
	return (output);
}

t_command	Request::parse_command(Extractor &str)
{
	t_command	output = {};
	Extractor*	substr = str.extract_to(" ", true);
	output.code = (substr->is_digits(3)) ? substr->to<std::string>() : "";
	output.name = (output.code.empty()) ? substr->to<std::string>() : "";
	delete substr;
	return (output);
}

t_params	Request::parse_params(Extractor &str)
{
	t_params	output;

	Extractor*	substr = str.extract_from(":", true);
	output = str.split();
	if (substr)
	{
		output.push_back(std::string(*substr));
	}
	delete substr;
	return (output);
}

std::ostream& operator<< (std::ostream& stream, const t_prefixe& prefixe)
{
	if (prefixe.server_name)
		stream << (*prefixe.server_name);
	else if (prefixe.pseudo)
	{
		stream << (*prefixe.pseudo);
		if (prefixe.user)
			stream << (*prefixe.user);
		if (prefixe.host)
			stream << (*prefixe.host);
	}
	return (stream);
}

std::ostream& operator<< (std::ostream& stream, const t_command& command)
{
	if (!command.name.empty())
		stream << command.name;
	else
		stream << command.code;
	return (stream);
}

std::ostream& operator<< (std::ostream& stream, const t_params& params)
{
	if (params.empty())
		return (stream);
	size_t	size = params.size();
	for (size_t idx = 0; idx < size; idx += 1)
		stream << params[idx] << ((idx != size - 1) ? " " : "");
	return (stream);
}

std::ostream& operator<< (std::ostream& stream, const t_message& request)
{
	if (request.valide == false)
		return (stream);
	if (request.prefixe)
		stream << (*request.prefixe) << " ";
	if (request.command.name.size() || request.command.code.size())
		stream << request.command << " ";
	stream << request.params;
	return (stream);
}
