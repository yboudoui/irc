/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/06 14:35:01 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WAGNER_HPP
# define WAGNER_HPP
# define DEBUG 1

# include <vector>
# include <map>
//# include "Request.hpp"
//# include "Response.hpp"
# include "SocketConnection.hpp"

class SocketConnection;
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
typedef bool (*(pfonc))(SocketConnection & user, t_request const &);

class Wagner {
	private:	
	//	std::vector<Channel*>	_Channels;
		std::vector<SocketConnection*>			_SocketConnections;
		
		std::map<std::string,pfonc>	_cmd;
		

	public:
		Wagner();
		~Wagner();
		
		
		void 			addUser(SocketConnection *  socket);
		
		void 	treatRequest(SocketConnection & socket, t_request_queue const & _requests);
	
		static bool	cmd_cap(SocketConnection & socket, t_request const &);
		static bool	cmd_nick(SocketConnection & socket, t_request const &);
		static bool	cmd_user(SocketConnection & socket, t_request const &);
		static bool	cmd_ping(SocketConnection & socket, t_request const &);
		static bool	cmd_quit(SocketConnection & socket, t_request const &);
		static bool	cmd_whois(SocketConnection & socket, t_request const &);
		static bool	cmd_mode(SocketConnection & socket, t_request const &);
		static bool	cmd_join(SocketConnection & socket, t_request const &);
		static bool	cmd_privmsg(SocketConnection & socket, t_request const &);
		static bool	cmd_kick(SocketConnection & socket, t_request const &);
		static bool	cmd_invite(SocketConnection & socket, t_request const &);
		static bool	cmd_topic(SocketConnection & socket, t_request const &);
};

#endif
