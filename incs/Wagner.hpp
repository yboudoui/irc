/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/08 18:43:29 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WAGNER_HPP
# define WAGNER_HPP

# include <vector>
# include <map>
# include "Colors.hpp"
# include "Message.hpp"
# include "SocketConnection.hpp"
# include "User.hpp"

class SocketConnection;
//# include "Channel.hpp"

# define DEBUG_CALL_WAGNER PRINT_DEBUG_CALL(YELLOW, Wagner)

class Wagner
{
	private:
		typedef Message (Wagner::*pfonc)(SocketConnection*, Message const &);
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
		void			popRequest(t_message_queue& requests);
		t_message_queue	treatRequest(SocketConnection* socket, t_message_queue& requests);

		Message	cmd_pass	(SocketConnection* socket, Message const &);
		Message	cmd_cap		(SocketConnection* socket, Message const &);
		Message	cmd_nick	(SocketConnection* socket, Message const &);
		Message	cmd_user	(SocketConnection* socket, Message const &);
		Message	cmd_ping	(SocketConnection* socket, Message const &);
		Message	cmd_quit	(SocketConnection* socket, Message const &);
		Message	cmd_whois	(SocketConnection* socket, Message const &);
		Message	cmd_mode	(SocketConnection* socket, Message const &);
		Message	cmd_join	(SocketConnection* socket, Message const &);
		Message	cmd_privmsg	(SocketConnection* socket, Message const &);
		Message	cmd_kick	(SocketConnection* socket, Message const &);
		Message	cmd_invite	(SocketConnection* socket, Message const &);
		Message	cmd_topic	(SocketConnection* socket, Message const &);
};

#endif
