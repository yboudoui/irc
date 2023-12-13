/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/13 18:42:11 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WAGNER_HPP
# define WAGNER_HPP

# include <vector>
# include <map>
# include "Channel.hpp"

class SocketConnection;
class Channel;
class User;

# define DEBUG_CALL_WAGNER PRINT_DEBUG_CALL(YELLOW, Wagner)

class Wagner
{
	private:
		typedef	std::map<std::string, Channel*>				t_channel_map;
		typedef Message* (Wagner::*pfonc)(SocketConnection*, Message*);
	//	std::vector<Channel*>	_Channels;
		std::map<std::string, pfonc>			_cmd;
		std::map<SocketConnection*,	User*>		_clients;
		std::string 							_hostname;
		int										_port;
		std::string 							_pass;
		t_channel_map							_channel_map;

	public:
		Wagner(std::string host, int port, std::string pass);
		~Wagner();

		void			addClient(SocketConnection *  socket);
		void			popRequest(t_message_queue& requests);
		void			treatRequest(SocketConnection* socket, t_message_queue& requests, t_message_queue& responses);

		Message*	cmd_pass	(SocketConnection* socket, Message*);
		Message*	cmd_cap		(SocketConnection* socket, Message*);
		Message*	cmd_nick	(SocketConnection* socket, Message*);
		Message*	cmd_user	(SocketConnection* socket, Message*);
		Message*	cmd_ping	(SocketConnection* socket, Message*);
		Message*	cmd_quit	(SocketConnection* socket, Message*);
		Message*	cmd_whois	(SocketConnection* socket, Message*);
		Message*	cmd_mode	(SocketConnection* socket, Message*);
		Message*	cmd_join	(SocketConnection* socket, Message*);
		Message*	cmd_privmsg	(SocketConnection* socket, Message*);
		Message*	cmd_kick	(SocketConnection* socket, Message*);
		Message*	cmd_invite	(SocketConnection* socket, Message*);
		Message*	cmd_topic	(SocketConnection* socket, Message*);
};

#endif
