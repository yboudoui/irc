/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_CREATED.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:44:46 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 08:24:14 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
RPL_CREATED (003)
:This server was created <date>
*/
std::string	RPL_CREATED()
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 003 ";
	output << ": This server was created " << CREATION_DATE;
	output << "\r\n";
	return (output.str());
}
