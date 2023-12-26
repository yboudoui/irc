/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responses.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:36:16 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 18:03:38 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "responses.hpp"

Response::Response(void)
{
	_pfonc_map[5]	= &Response::__263;
	_pfonc_map[7]	= &Response::_ERR_NONICKNAMEGIVEN;
	_pfonc_map[8]	= &Response::_ERR_ERRONEUSNICKNAME;
	_pfonc_map[9]	= &Response::_ERR_NICKNAMEINUSE;
	_pfonc_map[10]	= &Response::_ERR_NEEDMOREPARAMS;
	_pfonc_map[14]	= &Response::_QUIT;

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

void	Response::setChannel(Channel* channel)
{
	_channel = channel;
}

void	Response::setMessage(std::string message)
{
	_message = message;
}

void	Response::operator () (int code, bool kill)
{
	if (_user->is_alive() == false)
		return ;
	MessageQueue	queue;

	for (size_t i = 0; i < MAX_REPONSE_CODE; i++)
	{
		if ((1u << i) & code)
			queue += new Message((this->*(_pfonc_map[i]))());
	}
	_user->setSendCache(queue.str());
	_user->is_alive(!kill);
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
	output << " 432 ";
	output << _user->nick_name.get();
	output << " : a nickname parameter is expected";
	return (output.str());
}

std::string	Response::_ERR_NICKNAMEINUSE(void)
{
	std::stringstream	output;

	output << ":" << _hostname;
	output << " 433 ";
	output << _user->nick_name.get();
	output << " :nickname already in use";
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

/*** CHANNEL MODES ***/

/*
ERR_NICKCOLLISION (436) // IDEM 433 ?
<nick> :<reason>
Returned by a server to a client when it detects a nickname collision
*/

/*
ERR_NOTOPLEVEL (413) ??? ON NE GERE PAS LES MASQUES ?
<mask> :<reason>
Used when a message is being sent 
to a mask without being limited to a top-level 
domain (i.e. * instead of *.au)
*/

/*
ERR_WILDTOPLEVEL (414)
<mask> :<reason>
Used when a message is being sent
to a mask with a wild-card for a top level domain (i.e. *.*)
*/

std::string	Response::_QUIT(void)
{
	std::stringstream	output;

	output << " QUIT " << _message;
	return (output.str());
}
