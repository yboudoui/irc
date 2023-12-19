/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageQueue.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:18:56 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/19 12:11:59 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MessageQueue.hpp"

MessageQueue::MessageQueue()
{

}

MessageQueue::~MessageQueue()
{

}

void	MessageQueue::clear(void)
{
	_queue.clear();
}

bool	MessageQueue::empty(void)
{
	return (_queue.empty());
}

Message*	MessageQueue::getLastMessage(void)
{
	Message*	output = NULL;
	if (_queue.empty())
		return (output);
	output = _queue.front();
	_queue.pop_front();
	return (output);
}

std::string	MessageQueue::str(void)
{
	Message				*tmp;
	std::stringstream	stream;
	while (!_queue.empty())
	{
		tmp = getLastMessage();
		stream << tmp << "\r\n";
		delete tmp;
	}
	return (stream.str());
}

MessageQueue&	MessageQueue::operator << (std::string& src)
{
	Extractor			extractor(src);
	t_available_string	line;

	line = extractor.extract_to("\r\n");
	while (line)
	{
		(*this) += new Message(line());
		line = extractor.extract_to("\r\n");
	}
	src = extractor.str();
	return (*this);
}

MessageQueue&	MessageQueue::operator += (Message* src)
{
	if (src == NULL)
		return (*this);
	_queue.push_back(src);
	return (*this);
}
/*
MessageQueue&	MessageQueue::operator += (MessageQueue& src)
{
	_queue.insert(_queue.end(), src._queue.begin(), src._queue.end());
	return (*this);
}
*/
std::ostream& operator<< (std::ostream& stream, const MessageQueue& queue)
{
	for (size_t i = 0; i < queue._queue.size(); i++)
		stream << queue._queue[i] << std::endl;
	return (stream);
}
