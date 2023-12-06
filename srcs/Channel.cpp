/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/06 16:20:17 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colors.hpp"
#include "Channel.hpp"

# define DEBUG_CALL_CHANNEL PRINT_DEBUG_CALL(RED, Channel)
Channel::Channel()
{
	DEBUG_CALL_CHANNEL
}

Channel::~Channel()
{
	DEBUG_CALL_CHANNEL
}
