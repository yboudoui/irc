/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_USERONCHANNEL.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:53:15 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 08:23:41 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
ERR_USERONCHANNEL (443)
<nick> <channel> [:<reason>]
Returned when a client tries to 
invite a user to a channel they're already on
*/
std::string	ERR_USERONCHANNEL(std::string nick, std::string channel, std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 443";
	output << " " << nick;
	output << " " << channel;
	output << " :" << reason;
	output << "\r\n";
	return (output.str());
}
