/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_NICKNAMEINUSE.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:51:24 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 08:22:34 by yboudoui         ###   ########.fr       */
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
	return (output.str());
}
