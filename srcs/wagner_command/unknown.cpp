/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unknown.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 06:46:00 by yboudoui          #+#    #+#             */
/*   Updated: 2024/01/04 08:18:16 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Wagner.hpp"

void	Wagner::cmd_unknown	(void)
{
	DEBUG_CALL_WAGNER_COMMAND
	user->send_message(RPL_TRYAGAIN(request->command.name));
}
