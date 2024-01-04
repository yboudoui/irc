/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_NOTEXTTOSEND.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:58:07 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 08:23:07 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
ERR_NOTEXTTOSEND (412)
:<reason>
Returned when NOTICE/PRIVMSG is used with no message given
*/
std::string	ERR_NOTEXTTOSEND(std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 412";
	output << " :" << reason;
	output << "\r\n";
	return (output.str());
}
