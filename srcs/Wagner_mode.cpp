/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner_mode.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/19 15:06:05 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Wagner.hpp"
#include <stdio.h>


enum ChannelModes {
    INVITE_ONLY     = 1 << 0,   // 00001
    TOPIC_ONLY_OP   = 1 << 1,   // 00010
    KEY_PROTECTED   = 1 << 2    // 00100
};

void setMode(int *modes, enum ChannelModes mode) {
    *modes |= mode;
}

void unsetMode(int *modes, enum ChannelModes mode) {
    *modes &= ~mode;
}

int isModeSet(int modes, enum ChannelModes mode) {
    return (modes & mode) != 0;
}
/*
void	Wagner::cmd_mode(void)
{
	DEBUG_CALL_WAGNER
	std::cout << request << std::endl;

}
*/

/*
define _WHOIS(pf, c, r, a a, d) "sd sdf sd sd";
 
    Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]
    
   If a user attempts to make themselves an operator using the "+o"
   flag, the attempt should be ignored.  There is no restriction,
   however, on anyone `deopping' themselves (using "-o").  Numeric
   Replies:

    ERR_NEEDMOREPARAMS (461) <command> :<reason>  Returned by the server by any command which requires more parameters than the number of parameters given 
    ERR_CHANOPRIVSNEEDED (482) <channel> :<reason>  Returned by any command requiring special channel privileges (eg. channel operator) to indicate the operation was unsuccessful 
    ERR_NOTONCHANNEL (442) <channel> :<reason>   Returned by the server whenever a client tries to perform a channel effecting command for which the client is not a member 

    RPL_BANLIST (367) 
    <channel> <banid> [<time_left> :<reason>]
    A ban-list item (See RFC); <time left> and <reason> are additions used by KineIRCd 
    RPL_ENDOFBANLIST (368)
    <channel> :<info>
    Termination of an RPL_BANLIST list 
    
    ERR_UNKNOWNMODE (472)
    <char> :<reason>
    Returned when a given mode is unknown 

    RPL_CHANNELMODEIS (324)
    <channel> <mode> <mode_params>

    ERR_NOSUCHNICK (401)
    <nick> :<reason> 
    Used to indicate the nickname parameter supplied to a command is currently unused 
    
    ERR_KEYSET (467)
    <channel> :<reason>
    Returned when the channel key for a channel has already been set 

    ERR_NOSUCHCHANNEL (403)
    <channel> :<reason> 
    Used to indicate the given channel name is invalid, or does not exist

    ERR_USERSDONTMATCH (502)
    :<reason> 
    Error sent to any user trying to view or change the user mode for a user other than themselves 

    RPL_UMODEIS (221)
    <user_modes> [<user_mode_params>]
    Information about a user's own modes. Some daemons have extended the mode command and certain modes take parameters (like channel modes). 

    ERR_UMODEUNKNOWNFLAG (501)
    :<reason> 
    Returned by the server to indicate that a MODE message was sent with a nickname parameter and that the mode flag sent was not recognised 
*/

    // Initialiser les modes à zéro
    int channelModes = 0;

    setMode(&channelModes, INVITE_ONLY);

    if (isModeSet(channelModes, INVITE_ONLY)) {
        printf("INVITE_ONLY est actif.\n");
    } else {
        printf("INVITE_ONLY n'est pas actif.\n");
    }
    unsetMode(&channelModes, INVITE_ONLY);
    if (isModeSet(channelModes, INVITE_ONLY)) {
        printf("INVITE_ONLY est actif.\n");
    } else {
        printf("INVITE_ONLY n'est pas actif.\n");
    }

