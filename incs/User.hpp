/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 22:55:26 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/06 13:30:13 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef User_HPP
# define User_HPP

# include <iostream>

class User {
	private:
		std::string			_username;
		std::string			_hostname;
		std::string			_servername;
		std::string			_realname;
		std::string			_nickname;

	public:
		User();
		~User();
};

#endif
