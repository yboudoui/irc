/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 06:31:15 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 09:07:23 by yboudoui         ###   ########.fr       */
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
}
