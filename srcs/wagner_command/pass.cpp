/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 06:31:15 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 11:58:12 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wagner.hpp"

void	Wagner::cmd_pass(void)
{
	DEBUG_CALL_WAGNER_COMMAND

	if (user->isConnected())
		return(user->send_message(ERR_ALREADYREGISTRED(user->nick_name)));
	if (request->params.empty())
		return(user->send_message(ERR_NEEDMOREPARAMS("", "PASS", "please type a password" )));

	std::string password = request->params.front();
	request->params.pop_front();
	user->connection_password.set(password);

	if (user->connection_password.get() != _pass)
	{
		user->send_message(ERR_PASSWDMISMATCH(user->nick_name, "Password mismatch"));
		//user->is_alive(false);
		return ;
	}
	else
	{
		user->connectionStep(_pass, 1);
	}
	
}
