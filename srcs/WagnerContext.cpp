/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WagnerContext.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 19:21:11 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/18 17:11:54 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wagner.hpp"

Wagner::Context::Context(IQueue::IEventListener* listener, std::string hostname)
{
	user = dynamic_cast<User*>(listener);
	if (user == NULL)
		throw std::runtime_error("Bad EventListener");
	requests += user->getReadCache();
	reply.setUser(user);
	reply.setHostName(hostname);
}

bool	Wagner::Context::valide(void)
{
	if (requests.empty() || !user->is_alive())
		return (false);
	curr_request = requests.getLastMessage();
	reply.setRequest(curr_request);
	return (true);
}

void	Wagner::Context::send(void)
{
	user->setSendCache(reply.str());
}

void	Wagner::Context::killConnection(void)
{
	user->is_alive(false);
}
