/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_TOPIC.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:54:49 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 17:55:41 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
RPL_TOPIC (332)
<channel> :<info>
Response to TOPIC when no topic is set
*/
std::string	RPL_TOPIC(std::string channel, std::string topic)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 332";
	output << " " << channel;
	output << " :" << topic;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
