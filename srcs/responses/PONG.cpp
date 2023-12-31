/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PONG.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:55:49 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 08:23:58 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

std::string	PONG(std::string server)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " PONG ";
	output << server;
	output << "\r\n";
	return (output.str());
}
