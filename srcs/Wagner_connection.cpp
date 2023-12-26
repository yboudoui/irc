/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner_connection.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 19:05:14 by sethomas         ###   ########.fr       */
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
	if (user->isConnected())
		return(user->setSendCache(ERR_ALREADYREGISTRED(user->nick_name.get())));
	if (request->params.empty())
		return(user->setSendCache(ERR_NEEDMOREPARAMS("", "PASS", "please type a password" )));
	if (request->params.front() != _pass)
		return(user->setSendCache(ERR_PASSWDMISMATCH(user->nick_name.get())));
	return (user->connectionStep());
}

void	Wagner::cmd_nick(void)
{
	DEBUG_CALL_WAGNER
	/* STEP #1 : check if the new nickname is already in use || valid */
	if (request->params.empty())
		return (user->setSendCache(ERR_NONICKNAMEGIVEN()));
	std::string nickname = request->params.front();
	if (nickname == "anonymous" || nickname.find_first_of("<>?/\\!%#@&$") != std::string::npos)
		return (user->setSendCache(ERR_ERRONEUSNICKNAME(nickname)));
	else
	{
		/* STEP #2 : check if the new nickname is already in use */
		for (t_clients::iterator it = _clients.begin(); it != _clients.end(); it++)
		{
//			std::cout << "TODO : le bug est ici :" << std::endl; QUEL BUG?
			if ((*it)->is_alive() && *it != user)
			{
				if ((*it)->nick_name.get() == nickname)
					return (user->setSendCache(ERR_NICKNAMEINUSE(nickname)));
			}
		}
		std::string oldnick = user->nick_name.get();
		user->nick_name.set(nickname);
		if (user->isConnected())
			user->setSendCache(NICK(oldnick, nickname));
		else
			user->connectionStep();
	}
}

void	Wagner::cmd_user(void)
{
	DEBUG_CALL_WAGNER
	size_t			size = request->params.size();
	std::string		params;

	if (size == 0 || size < 4)
		return(user->setSendCache(ERR_NEEDMOREPARAMS("", "user")));
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
	if (user->isConnected())
	{
		user->setSendCache(RPL_WELCOME(user)); //001
		user->setSendCache(RPL_YOURHOST()); //002
		user->setSendCache(RPL_CREATED()); //003
		user->setSendCache(RPL_MYINFO()); //004
		return ;
	}
	user->setSendCache(ERR_PASSWDMISMATCH(user->nick_name.get()));
	user->is_alive(false);
}
