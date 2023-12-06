/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/06 12:38:28 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WAGNER_HPP
# define WAGNER_HPP
# define DEBUG 1

# include <vector>
# include <map>
//# include "Request.hpp"
//# include "Response.hpp"
# include "UserSocket.hpp"
//# include "Channel.hpp"

/*
	SocketConnection
	Client
	Channels

class BSCall
{
public:
	static Option* Factory(std::istream& is){return new Option();}	
};
 
typedef Option* (*PF)(std::istream&);
std::map<std::string, PF> io_map;
 
io_map["BSCall"]=&BSCall::Factory;
Option* option = io_map["BSCall"](std::cin);

*/
typedef bool (*(pfonc))(UserSocket & user, t_request const &);

class Wagner {
	private:	
	//	std::vector<Channel*>	_Channels;
		std::vector<UserSocket*>			_UserSockets;
		
		std::map<std::string,pfonc>	_cmd;
		

	public:
		Wagner();
		~Wagner();
		
		
		void 			addUser(UserSocket *  user);
		
		t_response const * 	treatRequest(t_request const & request);
		static bool	cmd_nick(UserSocket & user, t_request const &);
		static bool	cmd_user(UserSocket & user, t_request const &);
		static bool	cmd_ping(UserSocket & user, t_request const &);
		static bool	cmd_quit(UserSocket & user, t_request const &);
		static bool	cmd_whois(UserSocket & user, t_request const &);
		static bool	cmd_mode(UserSocket & user, t_request const &);
		static bool	cmd_join(UserSocket & user, t_request const &);
		static bool	cmd_privmsg(UserSocket & user, t_request const &);
		static bool	cmd_kick(UserSocket & user, t_request const &);
		static bool	cmd_invite(UserSocket & user, t_request const &);
		static bool	cmd_topic(UserSocket & user, t_request const &);
};

#endif
