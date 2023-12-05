/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/05 15:51:17 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WAGNER_HPP
# define WAGNER_HPP

# include <vector>
# include "Request.hpp"
# include "Response.hpp"
# include "UserSocket.hpp"
//# include "Channel.hpp"
//# include "User.hpp"

/*
	SocketConnection
	Client
	Channels
*/

class Wagner {
	private:
		//std::vector<Channel*>			_Channels;
	
		std::vector<UserSocket*>	_UserSockets;

	public:
		Wagner();
		~Wagner();
		
		
		void 			addUser(UserSocket *  user);
		
		t_response const * 	treatRequest(t_request const & request);
};

#endif
