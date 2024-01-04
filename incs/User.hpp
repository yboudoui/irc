/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 09:25:25 by yboudoui         ###   ########.fr       */
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
#include "Message.hpp"
# include <string>
# include <vector>

class Channel;
# define DEBUG_CALL_USER PRINT_DEBUG_CALL(RED, User)

# define DEBUG_CALL_USER_DESTRUCTOR \
	PRINT_DEBUG_CALL_MESSAGE(RED, "", User, RESET << " -> ")


class User
	: public SocketConnection
	, public predicate<User*>
{
	private:
		int										_connection_complete;
		typedef	std::map<std::string, Channel*>	t_channels;
		t_channels								_channels;
		static User*							_debug;

	public:
		static void debug(User*);
		User(IQueue &queue, int fd);
		~User();

		get_set<std::string>	user_name;
		get_set<std::string>	host_name;
		get_set<std::string>	server_name;
		get_set<std::string>	real_name;
		std::string		nick_name;
		get_set<std::string>	connection_password;
		
		bool	isConnected() const;
		void	connectionStep();
		void	sendToAllChannels(std::string message);

		void	join(Channel* channel);
		void	quitAllChannels(void);
		void	quit(Channel* channel);
		bool	send(std::string channelName, std::string message);
		void	sendTo(Channel* channel, std::string msg);
		bool	read_message(Message** msg);
		void	send_message(std::string msg);
		bool	operator () (User*);
};

predicate<User*>&	nickName(std::string);

#endif
