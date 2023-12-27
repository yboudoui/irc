/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_YOURHOST.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:44:01 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/27 18:03:46 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
RPL_YOURHOST (002)
:Your host is <servername>, running version <version>
*/
std::string	RPL_YOURHOST()
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 002 ";
	output << ": Your host is " << SERVERNAME;
	output << ", running version " << VERSION;
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
