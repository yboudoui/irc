/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/08 13:40:42 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WAGNER_HPP
# define WAGNER_HPP

# include <vector>
# include <map>
# include "Colors.hpp"
# include "SocketConnection.hpp"
# include "User.hpp"

class SocketConnection;
//# include "Channel.hpp"


# define DEBUG_CALL_WAGNER PRINT_DEBUG_CALL(MAGENTA, Wagner)

class Wagner {
	private:
		typedef t_message (Wagner::*pfonc)(SocketConnection*, t_message const &);
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
