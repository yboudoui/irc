/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_ALREADYREGISTERED.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:52:21 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 08:21:24 by yboudoui         ###   ########.fr       */
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
	return (output.str());
}
