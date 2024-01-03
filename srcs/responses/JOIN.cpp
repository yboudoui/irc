/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:56:58 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/03 12:42:27 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
KICK
*/
std::string	JOIN(std::string user, std::string channel)
{
	std::stringstream	output;

	output << ":" <<  user;
	output << " JOIN ";
	output << "#" << channel;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
