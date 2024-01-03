/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:16:55 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/03 13:56:55 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_HPP
# define SIGNAL_HANDLER_HPP

# include <signal.h>

class SignalHandler
{
	public:
		SignalHandler(void);
		~SignalHandler();
		bool	keep_running(void);

	private:
		struct sigaction	_signals[2];
		static	bool		_stop;
		static	void		_stop_loop_handler(int sig_value);
};

#endif
