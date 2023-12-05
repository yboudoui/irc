/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:04:51 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/05 12:18:17 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include "SocketBind.hpp"

/*
nc 127.0.0.1 8080 
ctrl+V ctrl+M  retrun (\r\n)
*/

int	main(int argc, char *argv[])
{
	int			port;
	std::string	password;

	argc -= 1;
	argv += 1;
	if (argc != 2) {
		std::cout << "This software require 2 argument : <port> <password>" << std::endl;
		return (1);
	}

	std::stringstream ss;
	ss << argv[0];
	ss >> port;
	// TODO CHECK SS >> return ERROR std::cerr
	password = argv[1];

	Queue	queue = Queue();

	SocketBind	sock(queue, port);

	std::cout << "localhost:" << port << std::endl;
	while (queue.event_loop());
	return (0);
}
