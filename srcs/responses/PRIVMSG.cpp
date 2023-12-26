/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:56:58 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 17:57:30 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
PRIVMSG
*/
std::string	PRIVMSG(std::string sender, std::string channel, std::string message)
{
	std::stringstream	output;

	output << ":" <<  sender;
	output << " PRIVMSG ";
	output << "#" << channel;
	output << " :" << message;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
