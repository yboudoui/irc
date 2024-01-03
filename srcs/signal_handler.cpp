/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:55:56 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/03 14:38:50 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.hpp"
#include <stdexcept>

bool	SignalHandler::_stop = false;

SignalHandler::SignalHandler(void)
{
	_signals[0] = (struct sigaction) { };
	_signals[1] = (struct sigaction) { };
	_signals[0].sa_handler = _stop_loop_handler;
	_signals[1].sa_handler = _stop_loop_handler;

	if (0
		|| sigaction(SIGINT, &_signals[0], NULL)
		|| sigaction(SIGQUIT, &_signals[1], NULL)
		)
		throw std::runtime_error("Unable to set sigaction handler");
}

SignalHandler::~SignalHandler()
{
}

void	SignalHandler::_stop_loop_handler(int sig_value)
{
	(void)sig_value;
	_stop = true;
}

bool	SignalHandler::keep_running(void)
{
	return (!_stop);
}
