/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_NONICKNAMEGIVEN.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:50:42 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 17:50:57 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
ERR_NONICKNAMEGIVEN (431)
:<reason>
Returned when a nickname parameter expected for a command isn't found
*/
std::string	ERR_NONICKNAMEGIVEN(std::string reason)
{
	std::stringstream	output;
	output << ":" << HOSTNAME;
	output << " 431";
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
