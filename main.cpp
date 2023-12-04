/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:04:51 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/04 12:13:36 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include "SocketBind.hpp"

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

	password = argv[1];

	Queue	queue = Queue();

	SocketBind	sock(queue, port);

	std::cout << "localhost:" << port << std::endl;
	while (queue.event_loop());
	return (0);
}
