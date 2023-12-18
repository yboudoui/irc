/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/18 16:45:26 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <map>
# include "User.hpp"
# include "available.hpp"
# include "IOrchestrator.hpp"

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

typedef enum e_user_right {
	NONE,
}	t_user_right;

class Channel
{
	private:
		std::string					_name;
		available<std::string>		_password;
		available<std::string>		_topic;
		//std::string					_key;
		//SocketConnection&				_operator;

		//int							_userLimit;
//		int							_modes;

		typedef	std::map<User*, t_user_right>	t_users_map;

		t_users_map	_users_map;
//		std::vector<SocketConnection&>	_UsersInvited;

	public:
		Channel();
		Channel(std::string name);
		~Channel();

		void		join(User* user);
		void		send(IOrchestrator::Context& ctx);
		std::string	getName(void);

};

class ChannelMap
{
	private:
		typedef	std::map<std::string, Channel*>	t_channel_map;
		t_channel_map							_channel_map;

	public:
		ChannelMap();
		~ChannelMap();
		Channel*	find(std::string name);
		Channel*	find_or_create(std::string name);
};

#endif
