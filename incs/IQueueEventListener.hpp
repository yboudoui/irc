/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IQueueEventListener.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:55:27 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/15 16:59:20 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IQUEUEEVENTLISTENER_HPP
# define IQUEUEEVENTLISTENER_HPP

class IQueueEventListener
{
	public:
		IQueueEventListener(void);
		bool			is_alive(bool alive = true);
		virtual void	read(void)	= 0;
		virtual void	write(void)	= 0;
		static void free(IQueueEventListener* p) { delete p; };
	protected:
		virtual	~IQueueEventListener(void) = 0;
	private:
		bool	_alive;
};

#endif
