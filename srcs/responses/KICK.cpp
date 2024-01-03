/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:56:58 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/03 10:47:15 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
KICK
*/
std::string	KICK(std::string user, std::string channel, std::string kickedUser, std::string reason)
{
	std::stringstream	output;

	output << ":" <<  user;
	output << " KICK ";
	output << "#" << channel;
	output << " " << kickedUser;
	output << " " << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
