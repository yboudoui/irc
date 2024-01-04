/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_ERRONEUSNICKNAME.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:51:52 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 08:22:09 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
ERR_ERRONEUSNICKNAME (432)
<nick> :<reason>
Returned after receiving a NICK message which contains a nickname
which is considered invalid, such as it's reserved ('anonymous')
or contains characters considered invalid for nicknames.
*/
std::string	ERR_ERRONEUSNICKNAME(std::string nick, std::string reason)
{
	std::stringstream	output;
	output << ":" << HOSTNAME;
	output << " 432";
	output << " " << nick;
	output << " :" << reason;
	output << "\r\n";
	return (output.str());
}
