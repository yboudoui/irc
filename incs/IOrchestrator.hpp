/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOrchestrator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:44:46 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/27 23:30:42 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IORCHESTRATOR_HPP
# define IORCHESTRATOR_HPP

# include "IQueue.hpp"

class IOrchestrator
{
	public:
		virtual void	treatEventListener(IQueue::IEventListener*)		= 0;
		virtual void	addEventListener(IQueue&, int)					= 0;
		virtual void	removeEventListener(IQueue::IEventListener*)	= 0;
};

#endif
