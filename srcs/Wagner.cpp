/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/06 18:52:18 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Colors.hpp"
# include "Wagner.hpp"
# include "SocketConnection.hpp"

# define DEBUG_CALL_WAGNER PRINT_DEBUG_CALL(MAGENTA, Wagner)
Wagner::Wagner()
{
	DEBUG_CALL_WAGNER
	_cmd.insert(std::make_pair("CAP", cmd_cap));
	_cmd.insert(std::make_pair("NICK", cmd_nick));
	_cmd.insert(std::make_pair("USER", cmd_user));
	_cmd.insert(std::make_pair("PING", cmd_ping));
	_cmd.insert(std::make_pair("QUIT", cmd_quit));
	_cmd.insert(std::make_pair("WHOIS", cmd_whois));
	_cmd.insert(std::make_pair("MODE", cmd_mode));
	_cmd.insert(std::make_pair("JOIN", cmd_join));
	_cmd.insert(std::make_pair("PRIVMSG", cmd_privmsg));
	_cmd.insert(std::make_pair("KICK", cmd_kick));
	_cmd.insert(std::make_pair("INVITE", cmd_invite));
	_cmd.insert(std::make_pair("TOPIC", cmd_topic));
}

Wagner::~Wagner()
{
	DEBUG_CALL_WAGNER
	// delete [] _events_list;
}

void 			Wagner::addUser(SocketConnection *  user)
{
	DEBUG_CALL_WAGNER
	_SocketConnections.push_back(user);
}

t_message_queue	Wagner::treatRequest(SocketConnection & socket, t_message_queue& requests)
{
	t_message_queue	responses;
	t_message		curr_req;
	(void)socket;

	std::map<std::string,pfonc>::iterator it;
	std::map<std::string,pfonc>::iterator ite = _cmd.end();

	while (requests.size())
	{
		curr_req = requests.front();
		requests.pop_front();
		it = _cmd.find(curr_req.command.name);
		if (it != ite)
		{
			t_message	response = (it->second)(socket, curr_req);
			PRINT_DEBUG_MESSAGE(BLUE,	"[" << curr_req << "]")
			PRINT_DEBUG_MESSAGE(GREEN,	"[" << response << "]")
			responses.push_back(response);
		}
		else {
			PRINT_DEBUG_MESSAGE(
			MAGENTA, "Wagner::cmd not found [" << curr_req.command.name << "]")
		}
	}

	// Analyse la CMD
	// traite la CMD (appel de fct membre)
		// NICK -> addUser( new User(t_message const & request ))
		// USER -> upd(user)
	// (! check si pb de traitement, verifier les erreurs de retour )

	// if CMD == NICK || USER
		// get &SocketConnection from request in _SocketConnections
		// user->upddate(request)
	// "NICK" => NickMethod(request);
	return (responses);
}

t_message	Wagner::cmd_nick(SocketConnection & user, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = false };

	(void)request;
	(void)user;
	return (output);
}

t_message	Wagner::cmd_user(SocketConnection & user, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = false };
	(void)request;
	(void)user;
	return (output);
}

t_message	Wagner::cmd_ping(SocketConnection & user, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = true };
	(void)request;
	(void)user;

	output.command.name = "PONG";
	output.params.push_back("localhost");
	return (output);
}

t_message	Wagner::cmd_quit(SocketConnection & user, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = false };
	(void)request;
	(void)user;
	return (output);
}

t_message	Wagner::cmd_whois(SocketConnection & user, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = true };
	(void)request;
	(void)user;

	output.command.code = "311";
	output.command.name = "RPL_WHOISUSER";
	output.params.push_back("the_user_pseudo");
	output.params.push_back("the_user_name");
	output.params.push_back("the_user_host");
	output.params.push_back(": Techno king");
	return (output);
}

t_message	Wagner::cmd_mode(SocketConnection & user, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = false };
	(void)request;
	(void)user;
	return (output);
}

t_message	Wagner::cmd_join(SocketConnection & user, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = false };
	(void)request;
	(void)user;
	return (output);
}

t_message	Wagner::cmd_privmsg(SocketConnection & user, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = false };
	(void)request;
	(void)user;
	return (output);
}

t_message	Wagner::cmd_kick(SocketConnection & user, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = false };
	(void)request;
	(void)user;
	return (output);
}

t_message	Wagner::cmd_invite(SocketConnection & user, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = false };
	(void)request;
	(void)user;
	return (output);
}

t_message	Wagner::cmd_topic(SocketConnection & user, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = false };
	(void)request;
	(void)user;
	return (output);
}

t_message	Wagner::cmd_cap(SocketConnection & user, t_message const &request)
{
	DEBUG_CALL_WAGNER
	t_message	output = {.valide = true };

	output.command.code = "001";
	output.params.push_back("the_user");
	output.params.push_back(":Welcome to the Internet Relay Network dan");
	(void)request;
	(void)user;
	return (output);
}
