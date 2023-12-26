/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_WHOISUSER.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:56:21 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 17:56:51 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

std::string	RPL_WHOISUSER(User * _user)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 311 ";
	output << _user->nick_name.get() << " ";
	output << _user->nick_name.get() << " ";
	output << _user->user_name.get() << " ";
	output << _user->host_name.get() << " ";
	output << _user->real_name.get() << " ";
	output << "\r\n";
	PRINT_DEBUG_MESSAGE(GREEN, output.str());
	return (output.str());
}
