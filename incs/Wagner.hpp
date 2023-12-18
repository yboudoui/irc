/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/18 15:23:16 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WAGNER_HPP
# define WAGNER_HPP

# include <set>
# include <map>
# include "IOrchestrator.hpp"
# include "Channel.hpp"
# include "User.hpp"
# include "responses.hpp"

# define DEBUG_CALL_WAGNER PRINT_DEBUG_CALL(YELLOW, Wagner)

class Wagner: public IOrchestrator
{
	public:
		Wagner(std::string host, int port, std::string pass);
		~Wagner();

		class Context : public IOrchestrator::Context {
			public:
				Context(IQueue::IEventListener*, std::string);
				bool		valide(void);
				void		killConnection(void);
				void		send(void);
				Context&	reply(Response::t_reponse_code);
				Message		*curr_request;
				User			*user;
				Response		_reply;
			private:
				MessageQueue	requests;
				MessageQueue	responses;
		};

		void	addEventListener(IQueue &queue, int fd_socketBind);
		void	treatEventListener(IQueue::IEventListener* listener);
		
	private:
		typedef void (Wagner::*pfonc)(Context&);
		typedef std::map<std::string, pfonc>			t_cmd_map;
		typedef std::set<User*>							t_clients;

		t_cmd_map								_cmd;
		t_clients								_clients;
		std::string 							_hostname;
		int										_port;
		std::string 							_pass;

		ChannelMap								_channel_map;

		void	cmd_pass		(Context&);
		void	cmd_cap			(Context&);
		void	cmd_nick		(Context&);
		void	cmd_user		(Context&);
		void	cmd_ping		(Context&);
		void	cmd_quit		(Context&);
		void	cmd_whois		(Context&);
		void	cmd_mode		(Context&);
		void	cmd_join		(Context&);
		void	cmd_privmsg		(Context&);
		void	cmd_kick		(Context&);
		void	cmd_invite		(Context&);
		void	cmd_topic		(Context&);
		void	cmd_notFound	(Context&);
};

#endif
