/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_CANNOTSENDTOCHAN.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:58:34 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 08:21:49 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
ERR_CANNOTSENDTOCHAN (404)
<channel> :<reason>	
Sent to a user who does not have the rights
to send a message to a channel
*/
std::string	ERR_CANNOTSENDTOCHAN(std::string channel, std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 404";
	output << " " << channel;
	output << " :" << reason;
	output << "\r\n";
	return (output.str());
}
