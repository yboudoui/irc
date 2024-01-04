/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 06:32:03 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 11:22:47 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wagner.hpp"

void	Wagner::cmd_nick(void)
{
	DEBUG_CALL_WAGNER_COMMAND
	/* STEP #1 : check if the new nickname is already in use || valid */
	if (request->params.empty())
		return (user->send_message(ERR_NONICKNAMEGIVEN()));
	std::string nickname = request->params.front();
	request->params.pop_front();
	if (0
		|| nickname == "anonymous"
		|| nickname == "localhost"
		|| nickname.find_first_of("<>?/\\!%#@&$") != std::string::npos)
		return (user->send_message(ERR_ERRONEUSNICKNAME(nickname)));

	/* STEP #2 : check if the new nickname is already in use */
	for (t_clients::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if ((*it)->is_alive() && *it != user)
		{
			if ((*it)->nick_name == nickname)
			{
				//user->nick_name = nickname;
				return (user->send_message(ERR_NICKNAMEINUSE(nickname)));
			}
		}
	}
				
	std::string oldnick;
	if (user->nick_name.size())
		oldnick = user->nick_name;
	else
		oldnick = nickname;
	//if (!oldnick.size())
	//	oldnick = nickname+"99";
	user->nick_name = nickname;
	user->send_message(NICK(oldnick, nickname));
	user->connectionStep();
	
}
