/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:10:23 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/06 12:38:08 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <sys/socket.h>
# include <string>
# include <cstring>
# include <map>
# include <deque>
# include "extractor.hpp"
# include "Colors.hpp"

typedef enum e_command {
	__NONE__,
	PRIVMSG,
	JOIN,
	QUIT,
	WHOIS,
	PING,
	USER,
	CAP,
	NICK
}	t_e_command;

typedef std::deque<std::string>	t_params;

/* <command> ::= <lettre> { <lettre> } | <nombre> <nombre> <nombre> */
typedef struct	s_command {
	std::string	command;
	int			code;
}	t_command;

/* <préfixe> ::= <nom de serveur> | <pseudo> [ '!' <utilisateur> ] [ '@' <hôte> ] */
typedef struct	s_prefix {
	std::string	*server_name;
	std::string	*pseudo;
	std::string	*user;
	std::string	*host;
}	t_prefixe;

/* <message> ::= [':' <préfixe> <espace> ] <command> <params> <crlf> */
typedef struct	s_request {
	t_prefixe	*prefixe;
	t_command	command;
	t_params	params;
//	UserSocket	&ref;
}	t_request;

std::ostream& operator<< (std::ostream& stream, const t_prefixe& prefixe);
std::ostream& operator<< (std::ostream& stream, const t_command& command);
std::ostream& operator<< (std::ostream& stream, const t_params& params);
std::ostream& operator<< (std::ostream& stream, const t_request& request);

typedef std::deque<t_request> t_request_queue;

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

		t_request_queue	get_requests(void);
};
#endif
