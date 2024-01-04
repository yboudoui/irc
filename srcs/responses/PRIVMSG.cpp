/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:56:58 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 08:24:03 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
PRIVMSG
*/
std::string	PRIVMSG(std::string sender, std::string channel, std::string message)
{
	std::stringstream	output;

	output << ":" <<  sender;
	output << " PRIVMSG ";
	output << "#" << channel;
	output << " :" << message;
	output << "\r\n";
	return (output.str());
}
