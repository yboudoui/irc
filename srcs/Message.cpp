/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/08 16:18:12 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colors.hpp"
#include "Message.hpp"

# define DEBUG_CALL_MESSAGE PRINT_DEBUG_CALL(YELLOW, Message)

Message::Message()
{
	//DEBUG_CALL_MESSAGE
		std::cout << YELLOW<< "Message::Message()" << RESET << std::endl;

	this->prefixe = NULL;
}

Message::~Message()
{
	if (this->command.code.size() || this->command.name.size())
		std::cout << this->command.code << " " << this->command.name << std::endl;
	std::cout << YELLOW<< "Message::~Message()" << RESET << std::endl;
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
