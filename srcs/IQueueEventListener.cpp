/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IQueueEventListener.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:57:55 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/15 16:59:18 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IQueueEventListener.hpp"

IQueueEventListener::IQueueEventListener(void)
	: _alive(true) {}


bool	IQueueEventListener::is_alive(bool alive)
{
	if (alive == false)
		_alive = false;
	return (_alive);
}

IQueueEventListener::~IQueueEventListener() {}

