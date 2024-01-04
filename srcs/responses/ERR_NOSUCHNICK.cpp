/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_NOSUCHNICK.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:49:36 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 08:23:02 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
ERR_NOSUCHNICK (401)
<nick> :<reason> 
Used to indicate the nickname parameter supplied 
to a command is currently unused 
*/
std::string	ERR_NOSUCHNICK(std::string userNickName, std::string channel, std::string nickname, std::string reason)
{
	std::stringstream	output;
	(void)nickname;
	output << ":" << HOSTNAME;
	output << " 401";
	output << " " << userNickName;
	if (channel.size())
		output << " #" << channel;
	output << " " << nickname;
	output << " :" << reason;
	output << "\r\n";
	return (output.str());
}
