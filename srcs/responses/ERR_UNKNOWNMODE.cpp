/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_UNKNOWNMODE.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:50:06 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 10:05:10 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
ERR_UNKNOWNMODE (472)
<char> :<reason>
Returned when a given mode is unknown 
*/
std::string	ERR_UNKNOWNMODE(std::string user, std::string channel, char c, std::string reason)
{
	std::stringstream	output;
	(void)user;
	(void)channel;
	output << ":" << HOSTNAME;
	output << " 472";
	output << " #" << channel;
	//output << " " << user;
	output << " " << c;
	output << " :" << reason;
	output << "\r\n";
	return (output.str());
}
