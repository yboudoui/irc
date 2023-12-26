/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responses.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:36:16 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 18:16:14 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
RPL_TRYAGAIN (263)
<command> :<info>
When a server drops a command without processing it, 
it MUST use this reply.
*/
std::string	RPL_TRYAGAIN(std::string command, std::string info)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " " << command;
	output << " :" << info;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}


std::string	NICK(std::string old, std::string newnick)
{
	std::stringstream	output;

	output << ":" << old;
	output << " NICK";
	output << " " << newnick;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}

