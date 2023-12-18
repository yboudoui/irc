/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOrchestrator.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:14:14 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/18 17:14:16 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IOrchestrator.hpp"

IQueue::IEventListener*	IOrchestrator::Context::eventListener(IQueue::IEventListener* listener)
{
//	if (listener != NULL)
		_listener = listener;
	return (_listener);
}
