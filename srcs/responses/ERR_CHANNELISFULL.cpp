/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_CHANNELISFULL.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:00:35 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 10:04:56 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
ERR_CHANNELISFULL (471) // canJoin
<channel> :<reason>
Returned when attempting to join
a channel which is set +l and is already full
*/
std::string	ERR_CHANNELISFULL(std::string user, std::string channel, std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 471";
	output << " " << user;
	output << " #" << channel;
	output << " :" << reason;
	output << "\r\n";
	return (output.str());
}
