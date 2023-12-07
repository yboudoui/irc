/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:04:51 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/07 17:00:03 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include "SocketBind.hpp"
#include "Wagner.hpp"

/*
nc 127.0.0.1 8080 
ctrl+V ctrl+M  retrun (\r\n)

RFC1459 (FR)
http://abcdrfc.free.fr/rfc-vf/rfc1459.html#23
RFC1459 (EN)
https://datatracker.ietf.org/doc/html/rfc1459#section-6
RETURN CODES 
https://www.alien.net.au/irc/irc2numerics.html

https://modern.ircdocs.horse/

QUESTIONS :
Pourquoi request.prefixe sont des  pointeurs sur std::string.
NB : je lis aue ==que les reponses sont toujours prefixees du nom du serveur 
	info a retrouver sur :
	http://chi.cs.uchicago.edu/chirc/irc.html#message-format
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
	// https://www.alien.net.au/irc/irc2numerics.html
	password = argv[1];

	Wagner		_wagner("localhost", port, password);
	
	Queue	queue = Queue();

	SocketBind	sock(_wagner, queue, port);

	std::cout << "localhost:" << port << std::endl;
	while (queue.event_loop());
	return (0);
}
