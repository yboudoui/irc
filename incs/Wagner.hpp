/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/07 15:25:56 by sethomas         ###   ########.fr       */
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
# include "User.hpp"

class SocketConnection;
class Wagner;
//# include "Channel.hpp"

typedef t_message (Wagner::*pfonc)(SocketConnection*, t_message const &);

class Wagner {
	private:
	//	std::vector<Channel*>	_Channels;
		std::map<std::string, pfonc>			_cmd;
		std::map<SocketConnection*,	User*>		_clients;
		std::string 							_hostname;
		int										_port;
		std::string 							_pass;

	public:
		Wagner(std::string host, int port, std::string pass);
		~Wagner();

		void			addClient(SocketConnection *  socket);

		t_message_queue	treatRequest(SocketConnection* socket, t_message_queue& requests);

		t_message	cmd_pass	(SocketConnection* socket, t_message const &);
		t_message	cmd_cap		(SocketConnection* socket, t_message const &);
		t_message	cmd_nick	(SocketConnection* socket, t_message const &);
		t_message	cmd_user	(SocketConnection* socket, t_message const &);
		t_message	cmd_ping	(SocketConnection* socket, t_message const &);
		t_message	cmd_quit	(SocketConnection* socket, t_message const &);
		t_message	cmd_whois	(SocketConnection* socket, t_message const &);
		t_message	cmd_mode	(SocketConnection* socket, t_message const &);
		t_message	cmd_join	(SocketConnection* socket, t_message const &);
		t_message	cmd_privmsg	(SocketConnection* socket, t_message const &);
		t_message	cmd_kick	(SocketConnection* socket, t_message const &);
		t_message	cmd_invite	(SocketConnection* socket, t_message const &);
		t_message	cmd_topic	(SocketConnection* socket, t_message const &);
};

#endif
