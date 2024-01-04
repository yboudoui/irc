/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 06:32:41 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 09:09:46 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wagner.hpp"

void	Wagner::cmd_user(void)
{
	DEBUG_CALL_WAGNER_COMMAND
	size_t			size = request->params.size();
	std::string		params;

	if (user->isConnected())
		return(user->send_message(ERR_ALREADYREGISTRED(user->nick_name)));

	if (size == 0 || size < 4)
		return(user->send_message(ERR_NEEDMOREPARAMS("", "user")));
	else
	{
		for (size_t idx = 0; idx < size; idx++)
		{
			switch (idx)
			{
				case 0 : user->user_name.set(request->params[idx]);	break;
				case 1 : user->host_name.set(request->params[idx]);	break;
				case 2 : user->server_name.set(request->params[idx]);	break;
				case 3 : user->real_name.set(request->params[idx]);	break;
				default: break;
			}
		}
		user->connectionStep();
	}
	if (user->connection_password.get() != _pass)
	{
		user->send_message(ERR_PASSWDMISMATCH(user->nick_name));
		user->is_alive(false);
		return ;
	}
	if (user->isConnected())
	{
		user->send_message(RPL_WELCOME(user)); //001
		user->send_message(RPL_YOURHOST()); //002
		user->send_message(RPL_CREATED()); //003
		user->send_message(RPL_MYINFO()); //004
		return ;
	}
	user->send_message(ERR_PASSWDMISMATCH(user->nick_name));
	user->is_alive(false);
}
