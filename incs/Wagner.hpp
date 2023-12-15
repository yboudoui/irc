/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/15 18:47:12 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WAGNER_HPP
# define WAGNER_HPP

# include <vector>
# include <map>
# include "IOrchestrator.hpp"
# include "Channel.hpp"
# include "User.hpp"

# define DEBUG_CALL_WAGNER PRINT_DEBUG_CALL(YELLOW, Wagner)

class Wagner: public IOrchestrator
{
	private:
		typedef void (Wagner::*pfonc)(SocketConnection*, Message*, t_message_queue&);
		typedef std::map<std::string, pfonc>			t_cmd_map;

		t_cmd_map								_cmd;
		std::map<SocketConnection*,	User*>		_clients;
		std::string 							_hostname;
		int										_port;
		std::string 							_pass;

		ChannelMap								_channel_map;

		void	cmd_pass	(SocketConnection* socket, Message*, t_message_queue&);
		void	cmd_cap		(SocketConnection* socket, Message*, t_message_queue&);
		void	cmd_nick	(SocketConnection* socket, Message*, t_message_queue&);
		void	cmd_user	(SocketConnection* socket, Message*, t_message_queue&);
		void	cmd_ping	(SocketConnection* socket, Message*, t_message_queue&);
		void	cmd_quit	(SocketConnection* socket, Message*, t_message_queue&);
		void	cmd_whois	(SocketConnection* socket, Message*, t_message_queue&);
		void	cmd_mode	(SocketConnection* socket, Message*, t_message_queue&);
		void	cmd_join	(SocketConnection* socket, Message*, t_message_queue&);
		void	cmd_privmsg	(SocketConnection* socket, Message*, t_message_queue&);
		void	cmd_kick	(SocketConnection* socket, Message*, t_message_queue&);
		void	cmd_invite	(SocketConnection* socket, Message*, t_message_queue&);
		void	cmd_topic	(SocketConnection* socket, Message*, t_message_queue&);


	public:
		Wagner(std::string host, int port, std::string pass);
		~Wagner();

		void	addEventListener(IQueueEventListener*  listener);
		void	treatEventListener(IQueueEventListener* listener);
};

#endif
