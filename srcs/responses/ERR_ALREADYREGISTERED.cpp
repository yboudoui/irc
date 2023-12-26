/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_ALREADYREGISTERED.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:52:21 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 17:52:42 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
ERR_ALREADYREGISTERED (462)
:<reason>
Returned by the server to any link which attempts to register again
*/
std::string	ERR_ALREADYREGISTRED(std::string nick, std::string reason)
{
	std::stringstream	output;
	output << ":" << HOSTNAME;
	output << " 462";
	output << " " << nick;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
