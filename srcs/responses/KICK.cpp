/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:56:58 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 08:23:51 by yboudoui         ###   ########.fr       */
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
	return (output.str());
}
