/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WagnerContext.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 19:21:11 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/18 15:18:38 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wagner.hpp"

Wagner::Context::Context(IQueue::IEventListener* listener, std::string hostname)
{
	user = dynamic_cast<User*>(listener);
	if (user == NULL)
		throw std::runtime_error("Bad EventListener");
	requests += user->getReadCache();
	_reply.setUser(user);
	_reply.setHostName(hostname);
}

bool	Wagner::Context::valide(void)
{
	if (requests.empty() || !user->is_alive())
		return (false);
	curr_request = requests.getLastMessage();
	_reply.setRequest(curr_request);
	return (true);
}

void	Wagner::Context::send(void)
{
	user->setSendCache(responses.str());
}

void	Wagner::Context::killConnection(void)
{
	user->is_alive(false);
}

Wagner::Context&	Wagner::Context::reply(Response::t_reponse_code code)
{
	if (user->is_alive() == false)
		return (*this);
	MessageQueue	tmp;
	tmp += _reply.response(code);
	user->setSendCache(tmp.str());

	//responses += _reply.response(code);
	return (*this);
}

