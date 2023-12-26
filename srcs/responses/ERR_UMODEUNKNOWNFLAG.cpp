/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_UMODEUNKNOWNFLAG.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:47:00 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 17:47:16 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
ERR_UMODEUNKNOWNFLAG (501)
:<reason> 
Returned by the server to indicate that a MODE 
message was sent with a nickname parameter 
and that the mode flag sent was not recognised
*/
std::string	ERR_UMODEUNKNOWNFLAG(std::string nickname, std::string reason)
{
	std::stringstream	output;

	(void)reason;
	output << ":" << HOSTNAME;
	output << " 501";
	output << " " << nickname;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
