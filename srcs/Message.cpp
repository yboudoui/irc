/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/13 13:53:13 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"


Message::Message()
	: valide(false)
{
	//DEBUG_CALL_MESSAGE
}

Message::Message(Message const& other)
	: valide(false)
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
	valide = true;
	prefixe	= parse_prefixe(_cache);
	command	= parse_command(_cache);
	params	= parse_params(_cache);
	return (*this);
}

t_prefixe	Message::parse_prefixe(Extractor &str)
{
	t_prefixe			output;
	t_available_string	_substr;

	if (str.size() < 2 || str[0] != ':')
		return (output);
//	if (str[1] == ' ')
//		throw std::runtime_error("Bad prefix format");
	str.erase(0, 1);

	_substr = str.extract_to(" ");
	if (!_substr)
		return (output);
	Extractor substr(_substr());
	output().host = substr.extract_from("@");
	output().user = substr.extract_from("!");
	if (output().host || output().user)
		output().pseudo(substr.str());
	if (output().pseudo)
		output().server_name(substr.str());
	return (output);
}

t_command	Message::parse_command(Extractor &str)
{
	t_command			output;
	t_available_string	_substr;

	_substr = str.extract_to(" ", true);
	if (!_substr)
		return (output);

	Extractor substr(_substr());
	output.code = (substr.is_digits(3)) ? substr.str() : "";
	output.name = (output.code.empty()) ? substr.str() : "";
	return (output);
}

t_params	Message::parse_params(Extractor &str)
{
	t_params			output;
	t_available_string	_substr;

	_substr = str.extract_from(":", true);
	output = str.split();
	if (_substr)
		output.push_back(_substr.value);
	return (output);
}

std::ostream& operator<< (std::ostream& stream, const t_prefixe& prefixe)
{
	if (!prefixe)
		return (stream);
	stream << prefixe().server_name();
	stream << prefixe().pseudo();
	stream << prefixe().user();
	stream << prefixe().host();
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
	if (message.prefixe)
		stream << message.prefixe << " ";
	if (message.command.name.size() || message.command.code.size())
		stream << message.command << " ";
	stream << message.params;
	return (stream);
}
/*
std::ostream& operator<< (std::ostream& stream, const Message* message)
{
	if (message != NULL)
		stream << *message;
	return (stream);
}
*/
std::ostream& operator<< (std::ostream& stream, const t_message_queue queue)
{
	for (size_t i = 0; i < queue.size(); i++)
		stream << queue[i] << std::endl;
	return (stream);
}

std::string& operator<< (std::string& str, t_message_queue queue)
{
	std::stringstream	stream;
	while (!queue.empty())
	{
		stream << queue.front() << "\r\n";
		queue.pop_front();
	}
	str += stream.str();
	return (str);
}

t_message_queue&	operator<< (t_message_queue& dest, t_message_queue src)
{
	dest.insert(dest.end(), src.begin(), src.end());
	return (dest);
}

t_message_queue& operator >> (t_message_queue& queue, std::string &str)
{
	Message				new_message;
	Extractor			extractor(str);
	t_available_string	line;

	line = extractor.extract_to("\r\n");
	while (line)
	{
		new_message >> line.value;
		queue.push_back(new_message);
		line = extractor.extract_to("\r\n");
	}
	str = extractor.str();
	return (queue);
}
