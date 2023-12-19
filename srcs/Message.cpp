/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/19 12:09:05 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

char	*Message::_color = (char *)WHITE;

void	Message::color(const char *c)
{
	_color = (char *)c;
	if (_color == NULL)
		_color = (char *)WHITE;
}

Message::Message(std::string raw_message)
{
//	DEBUG_CALL_MESSAGE
	Extractor	_cache(raw_message);
	prefixe	= parse_prefixe(_cache);
	command	= parse_command(_cache);
	params	= parse_params(_cache);
	PRINT_DEBUG_MESSAGE(_color, "\t" << this)
}

Message::Message(Message const& other)
	: prefixe(other.prefixe)
	, command(other.command)
	, params(other.params)
{
	DEBUG_CALL_MESSAGE
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
//	if (str[1] == ' ')
//		throw std::runtime_error("Bad prefix format");
	str.erase(0, 1);

	struct s_prefixe t;
	_substr = str.extract_to(" ");
	if (!_substr)
		return (output);
	Extractor substr(_substr());
	t.host = substr.extract_from("@");
	t.user = substr.extract_from("!");
	if (t.host || t.user)
		t.pseudo(substr.str());
	if (!t.pseudo)
		t.server_name(substr.str());
	output(t);
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
