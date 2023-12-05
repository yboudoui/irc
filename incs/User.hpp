/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/05 14:11:53 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include "SocketConnection.hpp"
# include "Request.hpp"

//<username> <hostname> <servername> <realname>

class User {
	private:
		std::string			_username;
		std::string			_hostname;
		std::string			_servername;
		std::string			_realname;

		std::string			_nickname;
		SocketConnection&	_socketConnection;

	public:
		User(t_request const & request);
		~User();
};

#endif
