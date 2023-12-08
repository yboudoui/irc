/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:10:23 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/08 17:05:03 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <sys/socket.h>
# include <deque>
# include "extractor.hpp"
# include "Message.hpp"

class Request {
	private:
		int			&_fd;
		Extractor	_cache;

		t_prefixe*	parse_prefixe(Extractor &str);
		t_command	parse_command(Extractor &str);
		t_params	parse_params(Extractor &str);

	public:
		Request(int &fd);
		~Request(void);

		t_message_queue	get_messages(void);
};
#endif
