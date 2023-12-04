/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:10:23 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/04 14:21:39 by sethomas         ###   ########.fr       */
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
typedef struct s_request {
	struct s_header {
		std::string							method, uri, version;
		std::map<std::string, std::string>	optional;
	}	header;
	std::string	body;
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

		bool	recv(t_request &request);
};
#endif
