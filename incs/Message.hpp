/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:10:23 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/12 13:01:52 by yboudoui         ###   ########.fr       */
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

struct	s_prefixe {
	t_available_string	server_name;
	t_available_string	pseudo;
	t_available_string	user;
	t_available_string	host;
};

typedef available<struct s_prefixe>	t_prefixe;

# define DEBUG_CALL_MESSAGE PRINT_DEBUG_CALL(YELLOW, Message)

class Message
{
	private:
		t_prefixe	parse_prefixe(Extractor &str);
		t_command	parse_command(Extractor &str);
		t_params	parse_params(Extractor &str);

	public:
		bool		valide;
		t_prefixe	prefixe;
		t_command	command;
		t_params	params;

		Message();
		Message(Message const& other);
		Message&	operator>>(std::string &str);
		~Message();
};

typedef std::deque<Message*> t_message_queue;
std::string&		operator << (std::string& str, t_message_queue queue);
t_message_queue&	operator << (t_message_queue& dest, t_message_queue src);
t_message_queue&	operator >> (t_message_queue& queue, std::string &str);

std::ostream& operator<< (std::ostream& stream, const t_prefixe& prefixe);
std::ostream& operator<< (std::ostream& stream, const t_command& command);
std::ostream& operator<< (std::ostream& stream, const t_params& params);
std::ostream& operator<< (std::ostream& stream, const t_message_queue queue);
std::ostream& operator<< (std::ostream& stream, const Message& message);
std::ostream& operator<< (std::ostream& stream, const Message* message);


#endif
