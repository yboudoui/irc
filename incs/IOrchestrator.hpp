/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOrchestrator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:44:46 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/18 17:12:57 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IORCHESTRATOR_HPP
# define IORCHESTRATOR_HPP

# include "IQueue.hpp"

class IOrchestrator
{
	public:
		virtual void	treatEventListener(IQueue::IEventListener*)	= 0;
		virtual void	addEventListener(IQueue&, int)				= 0;
		class Context {
			public:
				IQueue::IEventListener*	eventListener(IQueue::IEventListener* listener);
				virtual void	send(void) = 0;
			private:
				IQueue::IEventListener*	_listener;
		};
};

#endif
