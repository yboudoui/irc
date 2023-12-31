/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 12:31:55 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

bool	new_message(std::string& raw_message, Message** output)
{
	(*output) = NULL;
	Extractor			extractor(raw_message);
	t_available_string	line;

	line = extractor.extract_to("\r\n");
	if (line)
		(*output) = new Message(line());
	raw_message = extractor.str();
	return (true && ((*output) != NULL));
}

Message::Message(std::string raw_message)
{
	Extractor	_cache(raw_message);
	prefixe	= parse_prefixe(_cache);
	command	= parse_command(_cache);
	params	= parse_params(_cache);
}

Message::~Message()
{
//	DEBUG_CALL_MESSAGE
}

t_prefixe	Message::parse_prefixe(Extractor &str)
{
	t_prefixe			output;
	t_available_string	_substr;

	if (str.size() < 2 || str[0] != ':')
		return (output);
	if (str[1] == ' ')
		throw std::runtime_error("Bad prefix format");
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

	_substr = str.extract_from(":");
	output = str.split();
	if (_substr)
		output.push_back(_substr());
	return (output);
}

std::ostream& operator<< (std::ostream& stream, const t_prefixe& prefixe)
{
	if (!prefixe)
		return (stream);
	if (prefixe().server_name)
		stream << ":" << prefixe().server_name();
	else
	{
		stream << prefixe().pseudo();
		if (prefixe().user)
			stream << "!" << prefixe().user();
		if (prefixe().host)
			stream << "@" << prefixe().host();
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
	if (message.prefixe)
		stream << message.prefixe << " ";
	if (message.command.name.size() || message.command.code.size())
		stream << message.command << " ";
	stream << message.params;
	return (stream);
}

std::ostream& operator<< (std::ostream& stream, const Message* message)
{
	if (message != NULL)
		stream << (*message);
	return (stream);
}

std::string& operator << (std::string& str, Message& message)
{
	std::stringstream	stream;
	stream << message << "\r\n";
	str += stream.str();
	return (str);
}

std::string& operator << (std::string& str, Message* message)
{
	if (message != NULL)
		str << (*message);
	return (str);
}

