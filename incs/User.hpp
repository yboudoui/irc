/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/20 08:51:05 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef User_HPP
# define User_HPP

# include "Colors.hpp"
# include "SocketConnection.hpp"
# include <string>

# define DEBUG_CALL_USER PRINT_DEBUG_CALL(YELLOW, User)

class User : public SocketConnection
{
	private:
		int					_connection_complete;
		std::string			_username;
		std::string			_hostname;
		std::string			_servername;
		std::string			_realname;
		std::string			_nickname;
		~User();

	public:
		User(IQueue &queue, int fd);

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
};

#endif
