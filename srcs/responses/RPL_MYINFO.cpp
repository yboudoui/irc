/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_MYINFO.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:45:21 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/27 18:07:33 by sethomas         ###   ########.fr       */
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
	output << ": " << SERVERNAME << " " << VERSION << " o itlk";
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
