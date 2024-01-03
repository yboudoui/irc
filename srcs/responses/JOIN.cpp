/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:56:58 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/03 16:40:42 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
KICK
*/
std::string	JOIN(User* user, std::string channel)
{
	std::stringstream	output;

	output << ":" <<  user->nick_name.get();
	output << "!" <<  user->user_name.get();
	output << "@" <<  user->host_name.get();
	output << " JOIN ";
	output << "#" << channel;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
