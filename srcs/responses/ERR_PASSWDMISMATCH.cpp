/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_PASSWDMISMATCH.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:52:49 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 17:53:04 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
ERR_PASSWDMISMATCH (464)
:<reason>
Returned by the PASS command to indicate the given password
was required and was either not given or was incorrect
*/
std::string	ERR_PASSWDMISMATCH(std::string nick, std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 464";
	output << " " << nick;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
