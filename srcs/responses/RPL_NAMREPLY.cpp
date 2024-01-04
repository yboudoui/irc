/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_NAMREPLY.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:01:38 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 08:26:01 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
RPL_NAMREPLY (474)
:<server> 353 <nickname> <channel> :[[@|+]<nick>] [@[|+]<nick>] ...
<channel> :<reason>

RPL_ENDOFNAMES
*/
std::string	RPL_NAMREPLY(std::string nickname, Channel *channel)
{
	std::stringstream	output;
	(void)nickname;
	output << ":" << HOSTNAME;
	output << " 353";
	output << " " << nickname;
	output << " = #" << channel->name;
	output << " : " << channel->getUserList();
	output << "\r\n";
	return (output.str());
}

std::string	RPL_ENDOFNAMES(std::string nickname, Channel *channel)
{
	std::stringstream	output;
	(void)nickname;
	output << ":" << HOSTNAME;
	output << " 366";
	output << " " << nickname;
	output << " #" << channel->name;
	output << " :End of /NAMES list";
	output << "\r\n";
	return (output.str());
}
