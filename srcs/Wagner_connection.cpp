/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner_connection.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/19 16:14:24 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Wagner.hpp"

void	Wagner::cmd_cap(void)
{
	DEBUG_CALL_WAGNER
}

void	Wagner::cmd_pass(void)
{
	DEBUG_CALL_WAGNER

	if (request->params.empty())
		return (reply(Response::ERR_NEEDMOREPARAMS));
	if (request->params.front() != _pass)
		return (reply(Response::ERR_PASSWDMISMATCH));
	return (user->connectionStep());
}

void	Wagner::cmd_nick(void)
{
	DEBUG_CALL_WAGNER

	/* STEP #1 : check if the new nickname is already in use || */
	if (request->params.empty())
		return (reply(Response::ERR_NONICKNAMEGIVEN, true));

	std::string nickname = request->params.front();
	if (nickname == "anonymous" || nickname.find_first_of("!%#@") != std::string::npos)
		return (reply(Response::ERR_ERRONEUSNICKNAME, true));
	else
	{
		/* STEP #2 : check if the new nickname is already in use */
		for (t_clients::iterator it = _clients.begin(); it != _clients.end(); it++)
		{
			if ((*it)->getNickname() != nickname)
				continue ;
			return (reply(Response::ERR_NICKNAMEINUSE, true));
		}
		user->setNickname(nickname);
		user->connectionStep();
	}
}

void	Wagner::cmd_user(void)
{
	DEBUG_CALL_WAGNER
	size_t			size = request->params.size();
	std::string		params;

	if (size == 0 || size < 4)
		return (reply(Response::ERR_NEEDMOREPARAMS, true));
	else
	{
		for (size_t idx = 0; idx < size; idx++)
		{
			switch (idx)
			{
				case 0 : user->setUsername(request->params[idx]);	break;
				case 1 : user->setHostname(request->params[idx]);	break;
				case 2 : user->setServername(request->params[idx]);	break;
				case 3 : user->setRealname(request->params[idx]);	break;
				default: break;
			}
		}
		user->connectionStep();
	}

	if (user->isConnected())
	{
		reply(Response::_001
			| Response::_002
			| Response::_003
			| Response::_004
			| Response::_005);
		_clients.insert(user);
		return ;
	}
	reply(Response::ERR_PASSWDMISMATCH, true);
}
