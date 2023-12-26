/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_NOTOPIC.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:54:19 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 17:54:33 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
RPL_NOTOPIC (331)
<channel> :<info>
Response to TOPIC when no topic is set
*/
std::string	RPL_NOTOPIC(std::string channel, std::string info)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 331";
	output << " " << channel;
	output << " :" << info;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}