/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_NEEDMOREPARAMS.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:41:29 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 17:41:53 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

std::string	ERR_NEEDMOREPARAMS(std::string channel, std::string cmd, std::string reason)
{
	std::stringstream	output;

	(void)channel;
	output << ":" << HOSTNAME;
	output << " 461";
	if (channel.size())
		output << " #" << channel;
	output << " " << cmd;
	output << " :" << reason;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
