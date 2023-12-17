/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IQueueEventListener.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:57:55 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/17 16:35:13 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IQueue.hpp"

IQueue::IEventListener::IEventListener(void)
	: _alive(true) {}


bool	IQueue::IEventListener::is_alive(bool alive)
{
	if (alive == false)
		_alive = false;
	return (_alive);
}

IQueue::IEventListener::~IEventListener() {}

