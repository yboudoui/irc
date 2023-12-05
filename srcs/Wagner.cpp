/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:05:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/05 14:13:35 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Colors.hpp"
#include "Wagner.hpp"

Wagner::Wagner()
{
	std::cout << MAGENTA << "Wagner constructor called" << RESET << std::endl;
}

Wagner::~Wagner()
{
	std::cout << MAGENTA << "Wagner destructor called" << RESET << std::endl;
	// delete [] _events_list;
}


void	Wagner::addRequest(t_request const & request)
{
	(void)request;
}
void	Wagner::addResponse(t_response const & response)
{
	(void)response;
}
		
t_response const * 	Wagner::getResponse(SocketConnection &socketConnection) const
{
	(void) socketConnection;
	return NULL;
}

t_response const * 	Wagner::treatRequest(t_request const & request)
{
	(void)request;
	
	// Analyse la CMD
	// traite la CMD (appel de fct membre)
		// NICK -> addUser( new User(t_request const & request ))
		// USER -> upd(user)
	// (! check si pb de traitement, verifier les erreurs de retour )
	
	return NULL;
}
