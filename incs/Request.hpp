/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:10:23 by yboudoui          #+#    #+#             */
/*   Updated: 2023/09/22 12:51:59 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <sys/socket.h>
# include <string>
# include <cstring>
# include <map>

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
		bool		parseHeader(std::string line);
		void		parseOptionalHeader(std::string line);

	public:
		Request(int fd);
		~Request(void);

		bool	recv(t_request &request);
};
#endif
