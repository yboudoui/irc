/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:10:23 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/11 12:38:49 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

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

# define DEBUG_CALL_MESSAGE PRINT_DEBUG_CALL(YELLOW, Message)

class Message;
typedef std::deque<Message*> t_message_queue;

class Message
{
	private:
		t_prefixe*	parse_prefixe(Extractor &str);
		t_command	parse_command(Extractor &str);
		t_params	parse_params(Extractor &str);

	public:
		bool		valide;
		t_prefixe	*prefixe;
		t_command	command;
		t_params	params;

		Extractor	_cache;
		typedef char* t_EOF;
		const static t_EOF EOF;
		Message();
		Message(Message const& other);
		Message(Extractor &str);
		Message& operator << (std::string & str);
		Message& operator << (const char* str);
		void operator << (t_EOF eof);
		~Message();
};

std::ostream& operator<< (std::ostream& stream, const t_prefixe& prefixe);
std::ostream& operator<< (std::ostream& stream, const t_command& command);
std::ostream& operator<< (std::ostream& stream, const t_params& params);
std::ostream& operator<< (std::ostream& stream, const t_message_queue queue);
std::ostream& operator<< (std::ostream& stream, const Message& message);
std::ostream& operator<< (std::ostream& stream, const Message* message);

t_message_queue& operator >> (t_message_queue& queue, std::string &str);


#endif
