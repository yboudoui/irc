/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:08:10 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/08 16:04:41 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colors.hpp"
# include "Message.hpp"
# include "Request.hpp"

Request::Request(int &fd): _fd(fd) {}

Request::~Request(void) {}

t_message_queue	Request::get_messages(void)
{
	t_message_queue			output;
	
	size_t					bytes_read = 0;
	const unsigned int		buff_len = 512;
	char					buff[buff_len] = {0};

	bytes_read = ::recv(_fd, buff, buff_len, 0);
	_cache.append(buff, bytes_read);

	Extractor	*line = _cache.extract_to("\r\n");
	std::cout << GREEN << "l. " << *line << RESET << std::endl;
	while (line != NULL)
	{
		Message				new_request;
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
	Extractor*	substr;
	substr = str.extract_to(" ", true);

	output.code = (substr->is_digits(3)) ? substr->to<std::string>() : "";
	output.name = (output.code.empty()) ? substr->to<std::string>() : "";
	delete substr;
	return (output);
}

t_params	Request::parse_params(Extractor &str)
{
	t_params	output;
	Extractor*	substr;

	substr = str.extract_from(":", true);
	output = str.split();
	if (substr)
		output.push_back(std::string(*substr));
	delete substr;
	return (output);
}

