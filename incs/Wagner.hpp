/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/08 17:08:54 by sethomas         ###   ########.fr       */
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

typedef MessageResponse (Wagner::*pfonc)(SocketConnection*, Message const &);

class Wagner {
	private:
		typedef MessageResponse (Wagner::*pfonc)(SocketConnection*, Message const &);
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
		t_message_reponse_queue	treatRequest(SocketConnection* socket, t_message_queue& requests);

		MessageResponse	cmd_pass	(SocketConnection* socket, Message const &);
		MessageResponse	cmd_cap		(SocketConnection* socket, Message const &);
		MessageResponse	cmd_nick	(SocketConnection* socket, Message const &);
		MessageResponse	cmd_user	(SocketConnection* socket, Message const &);
		MessageResponse	cmd_ping	(SocketConnection* socket, Message const &);
		MessageResponse	cmd_quit	(SocketConnection* socket, Message const &);
		MessageResponse	cmd_whois	(SocketConnection* socket, Message const &);
		MessageResponse	cmd_mode	(SocketConnection* socket, Message const &);
		MessageResponse	cmd_join	(SocketConnection* socket, Message const &);
		MessageResponse	cmd_privmsg	(SocketConnection* socket, Message const &);
		MessageResponse	cmd_kick	(SocketConnection* socket, Message const &);
		MessageResponse	cmd_invite	(SocketConnection* socket, Message const &);
		MessageResponse	cmd_topic	(SocketConnection* socket, Message const &);
};

#endif
