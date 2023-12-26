/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_CHANNELMODEIS.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:49:07 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 17:49:24 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
RPL_CHANNELMODEIS (324)
<channel> <mode> <mode_params>
*/
std::string	RPL_CHANNELMODEIS(std::string nickname, Channel* channel)
{
	std::stringstream	output;
	(void)nickname;
	output << ":" << HOSTNAME;
	output << " 324";
	output << " " << nickname;
	output << " #" << channel->name.get();
	output << " " << channel->getChannelModes();
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
