/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/06 13:28:40 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <vector>
# include <map>
# include "SocketConnection.hpp"

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
/*

*/

class Channel {
	private:
		std::string					_name;
		//std::string					_topic;
		//std::string					_key;
		//SocketConnection&					_operator;

		//int							_userLimit;
		//int							_mode;
		
		//std::map<SocketConnection&, int>	_Users; // int -> rights (operator)
		//std::vector<SocketConnection&>	_UsersInvited;

	public:
		Channel();
		~Channel();
};

#endif
