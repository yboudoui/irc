/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERR_TOOMANYTARGETS.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:59:01 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 08:23:22 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

/*
ERR_TOOMANYTARGETS (407)
<target> :<reason> 
The given target(s) for a
command are ambiguous in that they relate to too many targets
*/
std::string	ERR_TOOMANYTARGETS(std::string target, std::string reason)
{
	std::stringstream	output;

	output << ":" << HOSTNAME;
	output << " 407";
	output << " " << target;
	output << " :" << reason;
	output << "\r\n";
	return (output.str());
}
