/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:04:51 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/03 14:43:55 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include "Queue.hpp"
#include "SocketBind.hpp"
#include "Wagner.hpp"
#include "signal_handler.hpp"

typedef struct {
	int			port;
	std::string	password;
}	t_input_params;

t_input_params	parse_input(int argc, char* argv[])
{
	t_input_params		output;
	std::stringstream	ss;

	argc -= 1;
	argv += 1;
	if (argc != 2)
		throw std::runtime_error("This software require 2 argument : <port> <password>");
	std::string	port_string(argv[0]);
	if (port_string.find_first_not_of("0123456789") != std::string::npos)
		throw std::runtime_error("This software require only number for argument <port>");
	ss << argv[0];
	ss >> output.port;
	output.password = argv[1];
	return (output);
}

void	server(t_input_params params)
{
	Queue			queue;
	Wagner			wagner(params.password);
	SocketBind		sock(wagner, queue, params.port);
	SignalHandler	sig;

	std::cout << "localhost:" << params.port << std::endl;

	while (1
		&& queue.event_loop(wagner)
		&& sig.keep_running()
	);
}

int	main(int argc, char *argv[])
{
	t_input_params	params;

	try
	{
		params = parse_input(argc, argv);
		server(params);
		return (0);
	}
	catch(const std::exception& e)
	{
		std::cerr << BOLD << RED << "Server stop: " << e.what() << RESET << std::endl;
		return (1);
	}
}
