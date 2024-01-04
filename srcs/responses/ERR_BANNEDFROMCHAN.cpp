/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_BANNEDFROMCHAN.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:01:05 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 08:21:41 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
ERR_BANNEDFROMCHAN (474) // canJoin
<channel> :<reason>
*/
std::string	ERR_BANNEDFROMCHAN(std::string channel, std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 474";
	output << " " << channel;
	output << " :" << reason;
	output << "\r\n";
	return (output.str());
}
