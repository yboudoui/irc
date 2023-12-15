/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IQueue.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:53:46 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/15 16:57:44 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IQUEUE_HPP
# define IQUEUE_HPP

# include "IQueueEventListener.hpp"

class IQueue {
	public:
		virtual void	subscribe(int fd, IQueueEventListener* event)	= 0;
		virtual void	unsubscribe(int fd)	= 0;
};

#endif

