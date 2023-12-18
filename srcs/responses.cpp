/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responses.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:36:16 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/18 17:02:11 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

Response::Response(void)
{
	_pfonc_map[1]	= &Response::__001;
	_pfonc_map[2]	= &Response::__002;
	_pfonc_map[3]	= &Response::__003;
	_pfonc_map[4]	= &Response::__004;
	_pfonc_map[5]	= &Response::__005;
	_pfonc_map[6]	= &Response::_RPL_WHOISUSER;
	_pfonc_map[7]	= &Response::__263;
	_pfonc_map[8]	= &Response::_ERR_NONICKNAMEGIVEN;
	_pfonc_map[9]	= &Response::_ERR_ERRONEUSNICKNAME;
	_pfonc_map[10]	= &Response::_ERR_NICKNAMEINUSE;
	_pfonc_map[11]	= &Response::_ERR_NEEDMOREPARAMS;
	_pfonc_map[12]	= &Response::_ERR_PASSWDMISMATCH;
	_pfonc_map[13]	= &Response::_PONG;
	_pfonc_map[14]	= &Response::_PRIVMSG;

}

void	Response::setHostName(std::string hostName)
{
	_hostname = hostName;
}

void	Response::setUser(User* user)
{
	// TODO check NULL
	_user = user;
}

void	Response::setRequest(Message* message)
{
	// TODO check NULL
	_request = message;
}

void		Response::setChannel(Channel* channel)
{
	_channel = channel;
}

void		Response::setMessage(std::string message)
{
	_message = message;
}

Response&	Response::operator |= (t_reponse_code code)
{
	for (size_t i = 1; i < MAX_REPONSE_CODE; i++)
	{
		if ((1u << i) & code)
		{
			pfonc	func = _pfonc_map[i];
			std::string a = (this->*func)();
			_queue += new Message(a);
		}
	}
	return (*this);
}

std::string	Response::str()
{
	std::string output = _queue.str();
	_queue.clear();
	return (output);
}
/*
MessageQueue&		Response::response(t_reponse_code code)
{
	_queue.clear();
	for (size_t i = 1; i < MAX_REPONSE_CODE; i++)
	{
		if ((1u << i) & code)
		{
			pfonc	func = _pfonc_map[i];
			std::string a = (this->*func)();
			_queue += new Message(a);
		}
	}
	return (_queue);
}
*/
std::string	Response::__001(void)
{
	std::stringstream	output;

	output << ":" << _hostname;
	output << " 001 ";
	output << _user->getNickname();
	output << " :Welcome to the Internet Relay Network ";
	output << _user->getNickname() << "!"+_user->getUsername() << "@"+_user->getHostname();
	return (output.str());
}

std::string	Response::__002(void)
{
	std::stringstream	output;

	output << ":" << _hostname;
	output << " 002 ";
	output << ": Your host is <servername>, running version <version>";
	return (output.str());
}

std::string	Response::__003(void)
{
	std::stringstream	output;

	output << ":" << _hostname;
	output << " 003 ";
	output << ": This server was created <date>";
	return (output.str());
}

std::string	Response::__004(void)
{
	std::stringstream	output;

	output << ":" << _hostname;
	output << " 004 ";
	output << ": <server_name> <version> <user_modes> <chan_modes>";
	return (output.str());
}

std::string	Response::__005(void)
{
	std::stringstream	output;

	output << ":" << _hostname;
	output << " 005";
	return (output.str());
}

std::string	Response::__263(void)
{
	std::stringstream	output;

	output << ":" << _hostname;
	output << " 263 ";
	output << _request->command.name;
	output << ": Unknown command: " << _request->command.name;
	return (output.str());
}

std::string	Response::_ERR_NONICKNAMEGIVEN(void)
{
	std::stringstream	output;

	output << ":" << _hostname;
	output << " 431 ";
	output << ": a nickname parameter is expected";
	return (output.str());
}

std::string	Response::_ERR_ERRONEUSNICKNAME(void)
{
	std::stringstream	output;

	output << ":" << _hostname;
	output << " 432";
	output << " " << _user->getNickname() << " : a nickname parameter is expected";
	return (output.str());
}

std::string	Response::_ERR_NICKNAMEINUSE(void)
{
	std::stringstream	output;

	output << ":" << _hostname;
	output << " 433";
	output << " " << _user->getNickname() << " :nickname already in use";
	return (output.str());
}

std::string	Response::_ERR_NEEDMOREPARAMS(void)
{
	std::stringstream	output;

	output << ":" << _hostname;
	output << " 461";
	output << " " << _request->command.name << " : command requires more parameters";
	return (output.str());
}

std::string	Response::_ERR_PASSWDMISMATCH(void)
{
	std::stringstream	output;

	output << ":" << _hostname;
	output << " 464 ";
	output << ": A Password is requiered to connect to " << _hostname;
	return (output.str());
}

std::string	Response::_PONG(void)
{
	std::stringstream	output;

	output << ":" << _hostname;
	output << " PONG ";
	output << _hostname;
	return (output.str());
}

std::string	Response::_RPL_WHOISUSER(void)
{
	std::stringstream	output;

	output << ":" << _hostname;
	output << " 311 ";
	output << _user->getNickname() << " ";
	output << _user->getNickname() << " ";
	output << _user->getUsername() << " ";
	output << _user->getHostname() << " ";
	output << _user->getRealname() << " ";
	return (output.str());
}

std::string	Response::_PRIVMSG(void)
{
	std::stringstream	output;

	output << ":" <<  _user->getNickname();
	output << " PRIVMSG ";
	output << "#" << _channel->getName();
	output << " " << _message;
	return (output.str());
}
