/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:10:23 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/07 16:02:23 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <sys/socket.h>
# include <deque>
# include "extractor.hpp"

typedef std::deque<std::string>	t_params;

typedef struct	s_command {
	std::string	name;
	std::string	code;
}	t_command;

typedef struct	s_prefix {
	std::string	*server_name;
	std::string	*pseudo;
	std::string	*user;
	std::string	*host;
}	t_prefixe;

typedef struct	s_message {
	bool		valide;
	t_prefixe	*prefixe;
	t_command	command;
	t_params	params;
}	t_message;

typedef std::deque<t_message> t_message_queue;

std::ostream& operator<< (std::ostream& stream, const t_prefixe& prefixe);
std::ostream& operator<< (std::ostream& stream, const t_command& command);
std::ostream& operator<< (std::ostream& stream, const t_params& params);
std::ostream& operator<< (std::ostream& stream, const t_message& request);


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
