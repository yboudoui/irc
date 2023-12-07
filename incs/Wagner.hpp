/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/07 10:57:23 by sethomas         ###   ########.fr       */
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
typedef t_message (*(pfonc))(SocketConnection & user, t_message const &);

class Wagner {
	private:
	//	std::vector<Channel*>	_Channels;
		std::vector<SocketConnection*>			_SocketConnections;
	
		std::map<std::string,pfonc>	_cmd;

	public:
		Wagner();
		~Wagner();

		void			addUser(SocketConnection *  socket);

		t_message_queue	treatRequest(SocketConnection & socket, t_message_queue& requests);

		static t_message	cmd_cap(SocketConnection & socket, t_message const &);
		static t_message	cmd_nick(SocketConnection & socket, t_message const &);
		static t_message	cmd_user(SocketConnection & socket, t_message const &);
		static t_message	cmd_ping(SocketConnection & socket, t_message const &);
		static t_message	cmd_quit(SocketConnection & socket, t_message const &);
		static t_message	cmd_whois(SocketConnection & socket, t_message const &);
		static t_message	cmd_mode(SocketConnection & socket, t_message const &);
		static t_message	cmd_join(SocketConnection & socket, t_message const &);
		static t_message	cmd_privmsg(SocketConnection & socket, t_message const &);
		static t_message	cmd_kick(SocketConnection & socket, t_message const &);
		static t_message	cmd_invite(SocketConnection & socket, t_message const &);
		static t_message	cmd_topic(SocketConnection & socket, t_message const &);
};

#endif
