/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/11 17:18:15 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colors.hpp"
#include "Message.hpp"


Message::Message()
{
	//DEBUG_CALL_MESSAGE

	this->prefixe = NULL;
}
/*
Message::Message(Extractor &str)
{
	valide = true;
	prefixe = parse_prefixe(str);
	command = parse_command(str);
	params = parse_params(str);
}
*/
Message::Message(Message const& other)
	: valide(other.valide)
	, prefixe(other.prefixe)
	, command(other.command)
	, params(other.params)
{
	//DEBUG_CALL_MESSAGE
}

Message::~Message()
{
	//DEBUG_CALL_MESSAGE
}

Message&	Message::operator>>(std::string &str)
{
	Extractor	_cache(str);
	valide	= true;
	prefixe	= parse_prefixe(	_cache);
	command	= parse_command(	_cache);
	params	= parse_params(		_cache);
	return (*this);
}

t_prefixe*	Message::parse_prefixe(Extractor &str)
{
	if (str.size() < 2 || str[0] != ':')
		return (NULL);
	if (str[1] == ' ')
		throw std::runtime_error("Bad prefix format");
	str.erase(0, 1);
	std::string *_substr = str.extract_to(" ");
	if (_substr == NULL)
		return (NULL);
	Extractor substr(*_substr);
	t_prefixe	*output = new t_prefixe;
	output->host = substr.extract_from("@");
	output->user = substr.extract_from("!");
	output->pseudo = (output->host || output->user) ? new std::string(substr.to<std::string>()) : NULL;
	output->server_name = (output->pseudo == NULL) ? new std::string(substr.to<std::string>()) : NULL;
	return (output);
}

t_command	Message::parse_command(Extractor &str)
{
	t_command	output = {};
	std::string*	_substr = str.extract_to(" ", true);
	if (_substr == NULL)
		return (output);
	Extractor substr(*_substr);

	output.code = (substr.is_digits(3)) ? substr.to<std::string>() : "";
	output.name = (output.code.empty()) ? substr.to<std::string>() : "";
	delete _substr;
	return (output);
}

t_params	Message::parse_params(Extractor &str)
{
	t_params	output;
	std::string*	_substr = str.extract_from(":", true);
	output = str.split();
	if (_substr)
		output.push_back(std::string(*_substr));
	delete _substr;
	return (output);
}

std::ostream& operator<< (std::ostream& stream, const t_prefixe& prefixe)
{
	if (prefixe.server_name)
		stream << ":" << (*prefixe.server_name);
	else if (prefixe.pseudo)
	{
		stream << ":" << (*prefixe.pseudo);
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

std::ostream& operator<< (std::ostream& stream, const Message& message)
{
	if (message.valide == false)
		return (stream);
	if (message.prefixe)
		stream << (*message.prefixe) << " ";
	if (message.command.name.size() || message.command.code.size())
		stream << message.command << " ";
	stream << message.params;
	return (stream);
}

std::ostream& operator<< (std::ostream& stream, const Message* message)
{
	if (message != NULL)
		stream << *message;
	return (stream);
}

std::ostream& operator<< (std::ostream& stream, const t_message_queue queue)
{
	for (size_t i = 0; i < queue.size(); i++)
		stream << queue[i] << std::endl;
	return (stream);
}

t_message_queue& operator >> (t_message_queue& queue, std::string &str)
{
	Message			*new_message;
	std::string		*line;

	Extractor extractor(str);
	line = extractor.extract_to("\r\n");
	while (line != NULL)
	{
		new_message = new Message();
		(*new_message) >> (*line);
		queue.push_back(new_message);
		line = extractor.extract_to("\r\n");
	}
	str = extractor.to<std::string>();
	return (queue);
}


