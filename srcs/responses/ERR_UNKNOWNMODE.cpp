/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_UNKNOWNMODE.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:50:06 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 17:50:39 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
ERR_UNKNOWNMODE (472)
<char> :<reason>
Returned when a given mode is unknown 
*/
std::string	ERR_UNKNOWNMODE(std::string channel, char c, std::string reason)
{
	std::stringstream	output;
	output << ":" << HOSTNAME;
	output << " 472";
	output << " #" << channel;
	output << " " << c;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
