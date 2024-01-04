/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_BADCHANNELKEY.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:00:11 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 10:04:39 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
ERR_BADCHANNELKEY (475) //canJoin
<channel> :<reason>
Returned when attempting to join a key-locked
channel either without a key or with the wrong key
*/
std::string	ERR_BADCHANNELKEY(std::string user,std::string channel, std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 475";
	output << " " << user;
	output << " #" << channel;
	output << " :" << reason;
	output << "\r\n";
	return (output.str());
}
