/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:10:23 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/08 16:51:01 by sethomas         ###   ########.fr       */
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

/*
typedef struct	s_message {
	bool		valide;
	t_prefixe	*prefixe;
	t_command	command;
	t_params	params;
}	Message;
*/

class Message {
	private:

	public:
		bool		valide;
		t_prefixe	*prefixe;
		t_command	command;
		t_params	params;
	
		Message();
		~Message();
};


class MessageResponse {
	private:

	public:
		bool		valide;
		t_prefixe	*prefixe;
		t_command	command;
		t_params	params;
	
		MessageResponse();
		~MessageResponse();
};


typedef std::deque<Message> t_message_queue;
typedef std::deque<MessageResponse> t_message_reponse_queue;

std::ostream& operator<< (std::ostream& stream, const t_prefixe& prefixe);
std::ostream& operator<< (std::ostream& stream, const t_command& command);
std::ostream& operator<< (std::ostream& stream, const t_params& params);
std::ostream& operator<< (std::ostream& stream, const Message& message);
std::ostream& operator<< (std::ostream& stream, const MessageResponse& message);


#endif
