/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_INVITEONLYCHAN.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:59:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/29 09:21:25 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
ERR_INVITEONLYCHAN (473) //canJoin
<channel> :<reason>
Returned when attempting to join a channel which is invite only without an invitation
*/
std::string	ERR_INVITEONLYCHAN(std::string nickname, std::string channel, std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 473";
	output << " " << nickname;
	output << " #" << channel;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
