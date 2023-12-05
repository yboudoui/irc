/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:10:23 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/05 14:16:15 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <sys/socket.h>
# include <string>
# include <cstring>
# include <map>

/* 
TODO Transformer s_request en msg IRC :
http://abcdrfc.free.fr/rfc-vf/rfc1459.html#23
*/

/* <params> ::= <espace> [ ':' <fin> | <milieu> <params> ] */
typedef struct	s_params {

}	t_params;

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
}	t_request;

std::ostream& operator<< (std::ostream& stream, const t_request& request);

class Request {
	private:
		int			_fd;
		std::string	_cache;
		t_request	*_request;

		bool		getNextLine(std::string &line);

	public:
		Request(int fd);
		~Request(void);

		bool		recv(t_request &request);
		t_request	parse_request(std::string str);
};
#endif
