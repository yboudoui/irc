/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_WELCOME.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:42:38 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 17:43:11 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
RPL_WELCOME (001)
:Welcome to the Internet Relay Network <nick>!<user>@<host>
*/

std::string	RPL_WELCOME(User * user)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 001 ";
	output << user->nick_name.get();
	output << " :Welcome to the Internet Relay Network ";
	output << user->nick_name.get() << "!" << user->user_name.get();
	output << "@"+ user->host_name.get();
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
