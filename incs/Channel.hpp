/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/13 15:55:17 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <vector>
# include <map>
# include <utility>
# include "Colors.hpp"
# include "extractor.hpp"
# include "User.hpp"

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


typedef	std::string										t_channel_name;
typedef	available<std::string>							t_channel_password;
typedef	std::pair<t_channel_name, t_channel_password>	t_channel_name_password;

typedef enum e_user_right {
	NONE,
}	t_user_right;

class Channel
{
	private:
		t_channel_name					_name;
		t_channel_password				_password;
		//std::string					_topic;
		//std::string					_key;
		//SocketConnection&				_operator;

		//int							_userLimit;
		//int							_mode;

		typedef	std::map<t_user_name, std::pair<User*, t_user_right> >	t_users_map;

		t_users_map	_users_map;
//		std::vector<SocketConnection&>	_UsersInvited;

	public:
		Channel();
		Channel(t_channel_name name);
		~Channel();

		Channel& operator = (const Channel &other);
		void	join(User* user);
};

typedef	std::map<t_channel_name, Channel*>				t_channel_map;

#endif
