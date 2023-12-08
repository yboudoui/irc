/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageResponse.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/08 16:47:01 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colors.hpp"
#include "Message.hpp"


MessageResponse::MessageResponse()
{
		std::cout << GREEN<< "MessageResponse::MessageResponse()" << RESET << std::endl;

	this->prefixe = NULL;
}

MessageResponse::~MessageResponse()
{
	if (this->command.code.size() || this->command.name.size())
		std::cout << this->command.code << " " << this->command.name << std::endl;
	std::cout << GREEN<< "MessageResponse::~MessageResponse()" << RESET << std::endl;
}

std::ostream& operator<< (std::ostream& stream, const MessageResponse& messageresponse)
{
	if (messageresponse.valide == false)
		return (stream);
	if (messageresponse.prefixe)
		stream << (*messageresponse.prefixe) << " ";
	if (messageresponse.command.name.size() || messageresponse.command.code.size())
		stream << messageresponse.command << " ";
	stream << messageresponse.params;
	return (stream);
}
