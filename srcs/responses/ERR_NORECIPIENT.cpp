/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_NORECIPIENT.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:57:38 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 08:22:48 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
ERR_NORECIPIENT (411)
:<reason>
Returned when no recipient is given with a command
*/
std::string	ERR_NORECIPIENT(std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 411";
	output << " :" << reason;
	output << "\r\n";
	return (output.str());
}
