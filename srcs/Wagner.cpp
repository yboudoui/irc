/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/18 15:17:50 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Wagner.hpp"

Wagner::Wagner(std::string host, int port, std::string pass)
	: _hostname(host)
	, _port(port)
	, _pass(pass)
{
	DEBUG_CALL_WAGNER
	_cmd.insert(std::make_pair("CAP",		&Wagner::cmd_cap));
	
	_cmd.insert(std::make_pair("PASS",		&Wagner::cmd_pass));
	_cmd.insert(std::make_pair("NICK",		&Wagner::cmd_nick));
	_cmd.insert(std::make_pair("USER",		&Wagner::cmd_user));
	
	_cmd.insert(std::make_pair("PING",		&Wagner::cmd_ping));
	_cmd.insert(std::make_pair("QUIT",		&Wagner::cmd_quit));
	_cmd.insert(std::make_pair("WHOIS",		&Wagner::cmd_whois));
	_cmd.insert(std::make_pair("MODE",		&Wagner::cmd_mode));
	_cmd.insert(std::make_pair("JOIN",		&Wagner::cmd_join));
	_cmd.insert(std::make_pair("PRIVMSG",	&Wagner::cmd_privmsg));
	_cmd.insert(std::make_pair("KICK",		&Wagner::cmd_kick));
	_cmd.insert(std::make_pair("INVITE",	&Wagner::cmd_invite));
	_cmd.insert(std::make_pair("TOPIC",		&Wagner::cmd_topic));
}

Wagner::~Wagner()
{
	DEBUG_CALL_WAGNER
	// delete [] _events_list;
	/*
	Command: ERROR
	Parameters: <reason>

	This message is sent from a server to a client to report a fatal error,
	before terminating the client’s connection.
	This MUST only be used to report fatal errors.
	Regular errors should use the appropriate numerics or the IRCv3 standard replies framework.
	*/
}

void	Wagner::addEventListener(IQueue &queue, int fd_socketBind)
{
	DEBUG_CALL_WAGNER
	User*	user = new User(queue, fd_socketBind);
	if (user == NULL)
		return ; // error
	_clients.insert(user);
}

void	Wagner::treatEventListener(IQueue::IEventListener* listener)
{
	Message::color(BLUE);
	Context	ctx(listener, _hostname);
	Message::color(GREEN);

	while (ctx.valide())
	{
		std::cout << "[" << ctx.curr_request->prefixe << "]" << ctx.curr_request << std::endl;
		t_cmd_map::iterator	it = _cmd.find(ctx.curr_request->command.name);
		if (it != _cmd.end())
			(this->*(it->second))(ctx);
		else
			cmd_notFound(ctx);
	}
	ctx.send();
}

void	Wagner::cmd_notFound	(Context& ctx)
{
	DEBUG_CALL_WAGNER
	ctx.reply(Response::_263);
}

void	Wagner::cmd_ping(Context& ctx)
{
	DEBUG_CALL_WAGNER
	ctx.reply(Response::PONG);
}

void	Wagner::cmd_quit(Context& ctx)
{
	DEBUG_CALL_WAGNER
	// TODO : envoyer message d'info aux autres utilisateurs
	ctx.killConnection();
}

void	Wagner::cmd_whois(Context& ctx)
{
	DEBUG_CALL_WAGNER
	ctx.reply(Response::RPL_WHOISUSER);
}

void	Wagner::cmd_join(Context& ctx)
{
	DEBUG_CALL_WAGNER
	Message*	request = ctx.curr_request;

	if (request->params.empty())
		return ((void)ctx.reply(Response::ERR_NEEDMOREPARAMS));

	std::vector< std::pair<std::string, available<std::string> > >	m;
	std::pair<std::string, available<std::string> >					new_pair;
	std::string														name;
	available<std::string>											password;
	size_t															index;

	for (index = 0; index < request->params.size(); index++)
	{
		name = request->params[index];
		if (name[0] != '#' && name[0] != '&')
			break ;
		new_pair.first = name.substr(1);
		m.push_back(new_pair);
	}

	for (size_t i = 0; i < m.size() && index < request->params.size(); i++)
		m[i].second(request->params[index++]);

/*	if (index < request.params.size())
		There is still some parameters.. error */

	for (size_t i = 0; i < m.size(); i++)
		_channel_map.find_or_create(m[i].first)->join(ctx.user);
}

void	Wagner::cmd_privmsg(Context& ctx)
{
	DEBUG_CALL_WAGNER
	Message	*request = ctx.curr_request;

	std::string	receiver, message = request->params.back();
	request->params.pop_back();

	while (!request->params.empty())
	{
		receiver = request->params.front().substr(1);
		request->params.pop_front();
		Channel*	channel = _channel_map.find(receiver);
		if (channel != NULL)
		{
			ctx._reply.setMessage(message);
			channel->send(ctx);
		}
		else
			continue; // but still an error or message to someone
	}
}

void	Wagner::cmd_kick(Context& ctx)
{
	DEBUG_CALL_WAGNER
	(void)ctx;
}

void	Wagner::cmd_invite(Context& ctx)
{
	DEBUG_CALL_WAGNER
	(void)ctx;
}

void	Wagner::cmd_topic(Context& ctx)
{
	DEBUG_CALL_WAGNER
	(void)ctx;
}
