/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IQueue.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:53:46 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/17 17:04:07 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IQUEUE_HPP
# define IQUEUE_HPP

class IQueue {
	public:
		class IEventListener
		{
			public:
				IEventListener(void);
				bool			is_alive(bool alive = true);
				virtual void	read(void)	= 0;
				virtual void	write(void)	= 0;
				static void free(IEventListener* p) { delete p; };
			protected:
				virtual	~IEventListener(void) = 0;
			private:
				bool	_alive;
		};

		virtual void	subscribe(int fd, IEventListener* event)	= 0;
		virtual void	unsubscribe(int fd)	= 0;
};

#endif

