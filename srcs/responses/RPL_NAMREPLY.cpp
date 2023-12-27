/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_NAMREPLY.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:01:38 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/27 18:04:09 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
RPL_NAMREPLY (474)
:<server> 353 <nickname> <channel> :[[@|+]<nick>] [@[|+]<nick>] ...
<channel> :<reason>
*/
std::string	RPL_NAMREPLY(std::string nickname, Channel *channel)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 353";
	output << " " << nickname;
	output << " #" << channel->name;
	output << " :" << channel->getUserList();
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
