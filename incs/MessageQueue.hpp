/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageQueue.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:17:28 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/17 18:04:03 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGEQUEUE_HPP
# define MESSAGEQUEUE_HPP

# include "Message.hpp"

class MessageQueue
{
	public:
		MessageQueue();
		~MessageQueue();
		bool			empty(void);
		void			clear(void);
		Message*		readLast(void);
		Message*		getLastMessage(void);
		std::string		str(void);
		MessageQueue&	operator += (Message*);
		MessageQueue&	operator += (std::string&);
		MessageQueue&	operator += (MessageQueue&);

		friend std::ostream& operator<< (std::ostream& stream, const MessageQueue& queue);
	private:
		std::deque<Message*>	_queue;
};


#endif
