/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responses.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:39:48 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/19 12:31:18 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSES_HPP
# define RESPONSES_HPP

# include <sstream>

# include "User.hpp"
# include "Channel.hpp"
# include "MessageQueue.hpp"

class Channel;
class Response
{
	public:
		Response(void);
		typedef enum e_reponse_code {
			NONE_REPONSE_CODE,
			_001					= (1u << 0),
			_002					= (1u << 1),
			_003					= (1u << 2),
			_004					= (1u << 3),
			_005					= (1u << 4),
			_263					= (1u << 5),
			RPL_WHOISUSER			= (1u << 6),
			ERR_NONICKNAMEGIVEN		= (1u << 7),
			ERR_ERRONEUSNICKNAME	= (1u << 8),
			ERR_NICKNAMEINUSE		= (1u << 9),
			ERR_NEEDMOREPARAMS		= (1u << 10),
			ERR_PASSWDMISMATCH		= (1u << 11),
			PONG					= (1u << 12),
			PRIVMSG					= (1u << 13),
			MAX_REPONSE_CODE		= 14,
		}	t_reponse_code;
		void			setHostName(std::string hostName);
		void			setUser(User* user);
		void			setRequest(Message* message);
		void			setChannel(Channel* channel);
		void			setMessage(std::string message);

		void	operator () (int code, bool kill = false);

	private:
		typedef std::string (Response::*pfonc)(void);
		pfonc		_pfonc_map[MAX_REPONSE_CODE + 1];
		std::string	_hostname;
		User		*_user;
		Message		*_request;
		Channel		*_channel;
		std::string _message;

		std::string	__001(void);
		std::string	__002(void);
		std::string	__003(void);
		std::string	__004(void);
		std::string	__005(void);

/*	RPL_TRYAGAIN (263) <command> :<info>
	When a server drops a command without processing it,it MUST use this reply.
*/		std::string	__263(void);

/*	ERR_NONICKNAMEGIVEN (431) :<reason>
	Returned when a nickname parameter expected for a command isn't found
*/		std::string	_ERR_NONICKNAMEGIVEN(void);

/*	ERR_ERRONEUSNICKNAME (432) <nick> :<reason> 
	Returned after receiving a NICK message which contains a nickname which is considered invalid 
	such as it's reserved ('anonymous') or contains characters considered invalid for nicknames.
*/		std::string	_ERR_ERRONEUSNICKNAME(void);

/*	ERR_NICKNAMEINUSE (433) <nick> :<reason> 
	Returned after receiving a NICK message which contains a nickname which is considered invalid 
	such as it's reserved ('anonymous') or contains characters considered invalid for nicknames.
*/		std::string	_ERR_NICKNAMEINUSE(void);

/*	ERR_NEEDMOREPARAMS (461) <command> :<reason> ""
	Returned by the server by any command which requires more parameters than the number of parameters given
*/		std::string	_ERR_NEEDMOREPARAMS(void);

/*	ERR_PASSWDMISMATCH (464) :<reason>
	Returned by the PASS command to indicate the given password was required and was either not given 
	or was incorrect
*/		std::string	_ERR_PASSWDMISMATCH(void);

		std::string	_PONG(void);
		std::string	_RPL_WHOISUSER(void);
		std::string	_PRIVMSG(void);

};

#endif
