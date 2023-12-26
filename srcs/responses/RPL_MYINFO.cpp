/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_MYINFO.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:45:21 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 17:45:46 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
RPL_MYINFO (004)
:<server_name> <version> <user_modes> <chan_modes>
*/
std::string	RPL_MYINFO()
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 004 ";
	output << ": <server_name> <version> <user_modes> <chan_modes>";
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
