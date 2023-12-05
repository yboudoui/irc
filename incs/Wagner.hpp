/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/05 14:11:37 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WAGNER_HPP
# define WAGNER_HPP

# include <vector>
# include "Request.hpp"
# include "Response.hpp"
# include "SocketConnection.hpp"
//# include "Channel.hpp"
# include "User.hpp"

/*
	SocketConnection
	Client
	Channels
*/

class Wagner {
	private:
	//	std::vector<Channel*>			_Channels;
	//	std::vector<User*>				_Users;
		std::vector<SocketConnection*>	_SocketConnections;
		std::vector<t_request*>			_Requests;

	public:
		Wagner();
		~Wagner();
		
		void 			addRequest(t_request const & request);
		void 			addResponse(t_response const & respsonse);
		
		void 			addUser(User *  const & user);
		
		t_response const * 	getResponse(SocketConnection &socketConnection) const;
		t_response const * 	treatRequest(t_request const & request);
};

#endif
