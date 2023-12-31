/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_INVITING.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:53:52 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 08:24:20 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
RPL_INVITING (341)
<nick> <channel>	
Returned by the server to indicate that the attempted INVITE
message was successful and is being passed onto the end client.
Note that RFC1459 documents the parameters in the reverse order. 
the format given here is the format used on production servers, 
and should be considered the standard reply above that given by RFC1459.
*/
std::string	RPL_INVITING(std::string userNick, std::string invitedNick, std::string channel)
{
	std::stringstream	output;

	(void)userNick;
	output << ":" << HOSTNAME;
	output << " 341";
	output << " " << userNick;
	output << " " << invitedNick;
	output << " #" << channel;
	output << "\r\n";
	return (output.str());
}
