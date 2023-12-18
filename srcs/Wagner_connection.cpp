/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner_connection.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/18 17:11:09 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Wagner.hpp"

void	Wagner::cmd_cap(Context& ctx)
{
	DEBUG_CALL_WAGNER
	(void)ctx;
}

void	Wagner::cmd_pass(Context& ctx)
{
	DEBUG_CALL_WAGNER

	Message*		request = ctx.curr_request;
	std::string		params;
	std::string		clientPass = request->params.front();

	if (!request->params.empty() && clientPass == _pass)
		return (ctx.user->connectionStep());
	if (clientPass != _pass)
		ctx.reply |= Response::ERR_PASSWDMISMATCH;
	else
		ctx.reply |= Response::ERR_NEEDMOREPARAMS;
	ctx.killConnection();
}

void	Wagner::cmd_nick(Context& ctx)
{
	DEBUG_CALL_WAGNER

	Message	*request = ctx.curr_request;

	/* STEP #1 : check if the new nickname is already in use || */
	if (request->params.empty())
	{
		ctx.reply |= Response::ERR_NONICKNAMEGIVEN;
		ctx.killConnection();
		return ;
	}

	std::string nickname = request->params.front();
	if (nickname == "anonymous" || nickname.find_first_of("!%#@") != std::string::npos)
	{
		ctx.reply |= Response::ERR_ERRONEUSNICKNAME;
		ctx.killConnection();
		return ;
	}
	else
	{
		/* STEP #2 : check if the new nickname is already in use */
		for (t_clients::iterator it = _clients.begin(); it != _clients.end(); it++)
		{
			if ((*it)->getNickname() != nickname)
				continue ;
			ctx.reply |= Response::ERR_NICKNAMEINUSE;
			return (ctx.killConnection());
		}
		ctx.user->setNickname(nickname);
		ctx.user->connectionStep();
	}
}

void	Wagner::cmd_user(Context& ctx)
{
	DEBUG_CALL_WAGNER
	Message*		request = ctx.curr_request;
	size_t			size = request->params.size();
	std::string		params;

	if (size == 0 || size < 4)
	{
		ctx.reply |= Response::ERR_NEEDMOREPARAMS;
		return (ctx.killConnection());
	}
	else
	{
		for (size_t idx = 0; idx < size; idx++)
		{
			switch (idx)
			{
				case 0 : ctx.user->setUsername(request->params[idx]);	break;
				case 1 : ctx.user->setHostname(request->params[idx]);	break;
				case 2 : ctx.user->setServername(request->params[idx]);	break;
				case 3 : ctx.user->setRealname(request->params[idx]);	break;
				default: break;
			}
		}
		ctx.user->connectionStep();
	}

	if (ctx.user->isConnected())
	{
		ctx.reply |= Response::_001;
		ctx.reply |= Response::_002;
		ctx.reply |= Response::_003;
		ctx.reply |= Response::_004;
		ctx.reply |= Response::_005;
		_clients.insert(ctx.user);
		return ;
	}
	ctx.reply |= Response::ERR_PASSWDMISMATCH;
	ctx.killConnection();
}

		/* post-registration greeting
		Upon successful completion of the registration process,
		the server MUST send, in this order, 
			the RPL_WELCOME (001),
			RPL_YOURHOST (002),
			RPL_CREATED (003),
			RPL_MYINFO (004),
			and at least one RPL_ISUPPORT (005) numeric to the client. 
			
		The server SHOULD then respond as though the client sent the LUSERS
		command and return the appropriate numerics. If the user has client 
		modes set on them automatically upon joining the network, 
		
		the server SHOULD send the client 
			the RPL_UMODEIS (221) reply
			or a MODE message with the client as target,
		preferably the former.
		
		The server MAY send other numerics and messages.
		
		The server MUST then respond as though the client sent it the MOTD command,
		
		i.e. it must send either the successful Message of the Day numerics or the ERR_NOMOTD (422) numeric.


		TODO =>
		RPL_WELCOME		(001) :Welcome to the Internet Relay Network <nick>!<user>@<host>
		RPL_YOURHOST	(002) :Your host is <servername>, running version <version> 
		RPL_CREATED		(003) :This server was created <date>
		RPL_MYINFO		(004) :<server_name> <version> <user_modes> <chan_modes> 
		RPL_ISUPPORT	(005)
		*/	


	/* ANNOUNCE ARRIVAL 
	SocketConnection*		_clientSocket;
	User*					_clientUser;

	Message	_clientOutput;
	_clientOutput.command.name = "PRIVMSG"; //433 ERR_NICKNAMEINUSE
	std::map<SocketConnection*,	User*>::iterator	it = _clients.begin();
	std::map<SocketConnection*,	User*>::iterator	ite = _clients.end();

	for ( ; it != ite ; it++)
	{
		if (_clientSocket != socket)
		{
		_clientSocket = it->first;
		_clientUser = it->second;

		_clientOutput.params.push_back(_clientUser->getNickname());
		_clientOutput.params.push_back(": A new user arrived on the server, say hello to " +_user->getNickname()+ "");	
		_clientSocket->insertResponse(_clientOutput);
		_clientOutput.params.clear();
		std::cout << ":A new user arrived : " << _clientUser->getNickname() << std::endl;
		}
	}
	*/
