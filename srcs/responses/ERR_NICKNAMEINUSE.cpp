/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_NICKNAMEINUSE.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:51:24 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 17:51:40 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
ERR_NICKNAMEINUSE (433)
<nick> :<reason>
Returned by the NICK command when the given nickname is already in use
*/
std::string	ERR_NICKNAMEINUSE(std::string nick, std::string reason)
{
	std::stringstream	output;
	output << ":" << HOSTNAME;
	output << " 433";
	output << " " << nick;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
