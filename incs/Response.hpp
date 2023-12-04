/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <yboudoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:32:01 by yboudoui          #+#    #+#             */
/*   Updated: 2023/09/23 14:08:23 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# define HTTP_VERSION "HTTP/1.1"
# include <iostream>
# include <sys/socket.h>
# include <string>
# include <map>

static std::map<std::string, std::string> _status_message_map;

typedef struct s_response {
	struct s_header {
		std::string							status_code;
		std::map<std::string, std::string>	optional;
	}	header;
	std::string	body;
}	t_response;

std::ostream& operator<< (std::ostream& stream, const t_response &response);

class Response
{
	private:
		std::string	_cache;
		t_response	_response;

	public:
		Response(void);
		~Response(void);

		void		statusCode(int status_code);
		std::string	&optinalHeader(std::string name);
		void		body(std::string body);
		std::string	str(void) const;
		friend std::ostream& operator<<(std::ostream& os, const Response &r);
};

std::ostream& operator<< (std::ostream& stream, const Response &response);
#endif
