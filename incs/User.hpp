/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/13 18:40:00 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef User_HPP
# define User_HPP

# include "Colors.hpp"
# include "SocketConnection.hpp"
# include <string>

class SocketConnection;
# define DEBUG_CALL_USER PRINT_DEBUG_CALL(YELLOW, User)

typedef std::string	t_user_name;
class User
{
	private:
		int					_connection_complete;
		std::string			_username;
		std::string			_hostname;
		std::string			_servername;
		std::string			_realname;
		std::string			_nickname;

	public:
		User();
		~User();

		void	setUsername		(std::string name);
		void	setHostname		(std::string name);
		void	setServername	(std::string name);
		void	setRealname		(std::string name);
		void	setNickname		(std::string name);

		std::string const &	getUsername		(void) const;
		std::string const &	getHostname		(void) const;
		std::string const &	getServername	(void) const;
		std::string const &	getRealname		(void) const;
		std::string const &	getNickname		(void) const;

		bool	isConnected() const;
		void	connectionStep();
		SocketConnection	*socket;
};

#endif
