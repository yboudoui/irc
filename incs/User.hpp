/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/28 16:56:15 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef User_HPP
# define User_HPP

# include "Colors.hpp"
# include "User.hpp"
# include "SocketConnection.hpp"
# include "getset.hpp"
# include "predicate.hpp"
# include "Channel.hpp"
# include <string>
# include <vector>

class Channel;
# define DEBUG_CALL_USER PRINT_DEBUG_CALL(YELLOW, User)

class User
	: public SocketConnection
	, public predicate<User*>
{
	private:
		int										_connection_complete;
		typedef	std::map<std::string, Channel*>	t_channels;
		t_channels								_channels;
		

	public:
		User(IQueue &queue, int fd);
		~User();

		get_set<std::string>	user_name;
		get_set<std::string>	host_name;
		get_set<std::string>	server_name;
		get_set<std::string>	real_name;
		get_set<std::string>	nick_name;
		get_set<std::string>	connection_password;
		
		bool	isConnected() const;
		void	connectionStep();
		void	sendToAllChannels(std::string message);

		void	join(Channel* channel);
		void	quitAllChannels(void);
		void	quit(Channel* channel);
		bool	send(std::string channelName, std::string message);
		void	sendTo(Channel* channel, std::string msg);
		bool	operator () (User*);
};

predicate<User*>&	nickName(std::string);

#endif
