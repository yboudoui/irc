/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/22 14:34:21 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WAGNER_HPP
# define WAGNER_HPP

# include <set>
# include <map>
# include "IOrchestrator.hpp"
# include "responses.hpp"

# define DEBUG_CALL_WAGNER PRINT_DEBUG_CALL(YELLOW, Wagner)

class Wagner: public IOrchestrator
{
	public:
		Wagner(std::string host, std::string pass);
		~Wagner();

		void	addEventListener(IQueue &queue, int fd_socketBind);
		void	treatEventListener(IQueue::IEventListener* listener);

	private:
		typedef void (Wagner::*pfonc)(void);
		typedef std::map<std::string, pfonc>			t_cmd_map;
		typedef std::set<User*>							t_clients;

		t_cmd_map								_cmd;
		t_clients								_clients;
		std::string 							_hostname;
		std::string 							_pass;

		ChannelMap								_channel_map;

// Context
		User*			user;
		Response		reply;
		Message*		request;
		MessageQueue	requests;

		void	cmd_pass		(void);
		void	cmd_cap			(void);
		void	cmd_nick		(void);
		void	cmd_user		(void);
		void	cmd_ping		(void);
		void	cmd_quit		(void);
		void	cmd_whois		(void);
		void	cmd_mode		(void);
		void	cmd_join		(void);
		void	cmd_privmsg		(void);
		void	cmd_kick		(void);
		void	cmd_invite		(void);
		void	cmd_topic		(void);
		void	cmd_notFound	(void);

		User*	findClient(std::string name);
};
#define SELEN_ERR_NEEDMOREPARAMS(cmd, reason)       "localhost 461 " + cmd + " :" + reason

#endif
