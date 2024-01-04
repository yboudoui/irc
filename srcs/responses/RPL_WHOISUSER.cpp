/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_WHOISUSER.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:56:21 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 11:17:54 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

std::string	RPL_WHOISUSER(User * _user)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 311 ";
	output << _user->nick_name << " ";
	//output << _user->nick_name << " ";
	output << _user->user_name.get() << " ";
	output << _user->host_name.get() << " ";
	output << _user->real_name.get() << " ";
	output << "\r\n";
	return (output.str());
}
