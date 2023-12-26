/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 16:14:59 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <map>
# include "available.hpp"
# include "responses.hpp"
# include "Message.hpp"
# include "User.hpp"


# include "getset.hpp"

class User;
class Response;
# define DEBUG_CALL_CHANNEL PRINT_DEBUG_CALL(RED, Channel)
/*
the channel ceases to exist when the last client leaves it

  The commands which may only be used by channel operators are:

        KICK    - Eject a client from the channel
        MODE    - Change the channel's mode
        INVITE  - Invite a client to an invite-only channel (mode +i)
        TOPIC   - Change the channel topic in a mode +t channel

a channel operator is identified by the '@' symbol next to their
   nickname whenever it is associated with a channel (ie replies to the
   NAMES, WHO and WHOIS commands).
*/
/*
CHANNEL MODES 
i ->
	invite-only channel flag;
	si actif on ne peut rejoindre le groupe
	que sur invitation d'un operators

t ->
	topic settable by channel operators only flag;
	si actif seul les operators peut changer le topic
	
k ->
	set a channel key (password)
	http://www.geekshed.net/2012/03/using-channel-keys/
	[/mode #channel +k channelkey]
	si actif + key, on ne peut se connecter
	au channel qu'avec la key 
	[/join #channel password]
	
o ->
	Give/take channel operator privilege
	https://wiki.mibbit.com/index.php/Channel_operator
	[/mode <#channel> +o <nickname>]
	
l ->
	set the user limit to channel;
	Takes a positive integer parameter.
	Limits the number of users who can 
	be in the channel at the same time.
*/

enum ChannelModes {
    INVITE_ONLY     = 1 << 0,   // 00001
    TOPIC_ONLY_OP   = 1 << 1,   // 00010
    KEY_PROTECTED   = 1 << 2,   // 00100
    USER_LIMIT		= 1 << 3    // 01000
};


typedef enum e_user_right {
	NONE,
	OPERATOR,
	INVITED,
}	t_user_right;


class Channel
{
	private:
		available<std::string>		_key;

		int							_modes;

		typedef	std::map<User*, t_user_right>	t_users_map;

		t_users_map	_users_map;

	public:
		get_set<std::string>	name;
		get_set<std::string>	topic;
		get_set<size_t>			limit;

		Channel();
		Channel(std::string name);
		~Channel();

		bool		join(User* user, std::string usr_password);
		void		remove(User* user);
		void		send(std::string senderNickname, std::string message);
		
		// getters
		std::string getChannelModes();
		bool		getMode(enum ChannelModes mode);
		std::string		getUserList();
	
		// setters 
		void	setMode(char op, enum ChannelModes mode);
		void	setKey(std::string pass);
		
		// checkers
		bool	isOperator(User* user);
		bool	isInChannel(User* user);
		bool	canJoin(User* user, std::string usr_password);

		// others
		int		countUser();
		User*	findUser(std::string nick);

		void	ProcessModeCmd(User* user, const std::string& command,t_params& params);
};

#endif
