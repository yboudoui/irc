/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_NOTOPIC.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:54:19 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 08:26:07 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
RPL_NOTOPIC (331)
<channel> :<info>
Response to TOPIC when no topic is set
*/
std::string	RPL_NOTOPIC(std::string nickname, std::string channel, std::string info)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 331";
	output << " " << nickname;
	output << " #" << channel;
	output << " :" << info;
	output << "\r\n";
	return (output.str());
}
