/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:04:51 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/03 11:11:55 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include "Queue.hpp"
#include "SocketBind.hpp"
#include "Wagner.hpp"
#include <signal.h>
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
NB : les reponses sont toujours prefixees du nom du serveur 
	info a retrouver sur :
	http://chi.cs.uchicago.edu/chirc/irc.html#message-format
*/
// 
// output >> ":" >> nickname >> "!" >> username >> "@" >> userhost;

static bool _stop_loop = false;
static void	stop_loop(int sig_value)
{
	(void)sig_value;
	_stop_loop = true;
}

int	main(int argc, char *argv[])
{
	int			port;
	std::string	password;
	std::string	hostname = "localhost";

	argc -= 1;
	argv += 1;
	if (argc != 2) {
		std::cerr << "This software require 2 argument : <port> <password>" << std::endl;
		return (1);
	}

	std::stringstream ss;
	ss << argv[0];
	ss >> port;
	// TODO : CHECK SS >> return ERROR std::cerr
	// https://www.alien.net.au/irc/irc2numerics.html
	password = argv[1];

	Queue	queue = Queue();
	Wagner	wagner(hostname, password);

	struct sigaction	signals[2] = {};
	signals[0].sa_handler = stop_loop;
	signals[1].sa_handler = SIG_IGN;

	if (sigaction(SIGINT, &signals[0], NULL) == -1 && sigaction(SIGINT, &signals[1], NULL) == -1)
	{
		std::cerr << "Unable to set sigaction handler" << std::endl;
		return (1);
	}
	try
	{
		SocketBind*	sock = new SocketBind(wagner, queue, port);

		std::cout << "localhost:" << port << std::endl;

		//TODO allocate Wagner then delete it
		while (queue.event_loop(wagner) && !_stop_loop );
		IQueue::IEventListener::free(sock);
		return (0);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}
	
	return (0);
}
