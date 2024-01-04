/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_NICKNAMEINUSE.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:51:24 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 10:13:14 by sethomas         ###   ########.fr       */
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
	(void)nick;
	output << ":" << HOSTNAME;
	output << " 433";
	output << " " << nick;
	output << " :" << reason;
	output << "\r\n";
	return (output.str());
}
