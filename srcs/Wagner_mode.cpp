/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wagner_mode.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:09:35 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/19 15:31:27 by sethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "Wagner.hpp"
#include <stdio.h>




int isModeSet(int modes, enum ChannelModes mode) {
    return (modes & mode) != 0;
}


/*
enum ChannelModes {
    INVITE_ONLY     = 1 << 0,   // 00001
    TOPIC_ONLY_OP   = 1 << 1,   // 00010
    KEY_PROTECTED   = 1 << 2,   // 00100
    USER_LIMIT		= 1 << 3    // 01000
};
*/

void processModeCommand(t_params& params, 
    const std::string& command,Channel& channel)
{
    (void)params;
    (void)command;
    char op = '+';  // Opérateur par défaut

    for (size_t i = 0; i < command.size(); ++i) {
        char c = command[i];
        if (c == '+' || c == '-') {
            // Mettre à jour l'opérateur en cours
            op = c;
        } else {
            // Traiter le mode en fonction de l'opérateur
            switch (c) {

                case 'i':
                    channel.setMode(op, INVITE_ONLY);
                    break;
                case 't':
                    channel.setMode(op, TOPIC_ONLY_OP);
                    break;
                case 'k':
                    channel.setMode(op, KEY_PROTECTED);
                    if (op == '+')
                    {
                        // Récupérer le paramètre suivant
                        channel.setKey("key");
                    }
                    break;
                case 'l':
                    channel.setMode(op, USER_LIMIT);
                    if (op == '+')
                    {
                        // Récupérer le paramètre suivant
                        channel.setLimit(10);
                    }
                    break;
                default:
                    // Gérer d'autres modes si nécessaire
                    break;
            }
        }
    }
}
/*
void	Wagner::cmd_mode(void)
{
	DEBUG_CALL_WAGNER


	if (request->params.empty())
		return (reply(Response::ERR_NEEDMOREPARAMS));

    t_params::iterator  it = request->params.begin();
    t_params::iterator  ite = request->params.end();

    Channel* channel = _channel_map.find("toto");
    for ( ; it != ite ; it++)
    {
        std::cout << "param :" << *it << std::endl;
    }
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
    Returned by the server to indicate that a MODE 
    message was sent with a nickname parameter 
    and that the mode flag sent was not recognised 
*/

    // Initialiser les modes à zéro
    /*
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
    */



/*
#include <iostream>
#include <string>
#include <vector>

// Fonction pour traiter la commande MODE IRC avec paramètres
void processModeCommand(const std::string& modeCommand, int& userMode, std::string& password, int& userLimit) {
    char modeOperator = '+';  // Opérateur par défaut
    std::vector<std::string> parameters;  // Pour stocker les paramètres des modes

    for (size_t i = 0; i < modeCommand.size(); ++i) {
        char mode = modeCommand[i];

        if (mode == '+' || mode == '-') {
            // Mettre à jour l'opérateur en cours
            modeOperator = mode;
        } else {
            // Traiter le mode en fonction de l'opérateur
            switch (mode) {
                case 'i':
                    userMode = (modeOperator == '+') ? (userMode | (1 << 0)) : (userMode & ~(1 << 0));
                    break;
                case 'k':
                    if (modeOperator == '+') {
                        // Récupérer le paramètre après le mode +k
                        password = modeCommand.substr(i + 1);
                        i = modeCommand.size();  // Sortir de la boucle après le mode +k
                    }
                    break;
                case 'l':
                    if (modeOperator == '+') {
                        // Récupérer le paramètre après le mode +l
                        userLimit = std::stoi(modeCommand.substr(i + 1));
                        i = modeCommand.size();  // Sortir de la boucle après le mode +l
                    }
                    break;
                default:
                    // Gérer d'autres modes si nécessaire
                    break;
            }
        }
    }
}

int main() {
    int userMode = 0;  // Mode initial
    std::string password;
    int userLimit = 0;

    // Exemple d'utilisation de la fonction avec une commande MODE IRC
    std::string modeCommand = "+ikmotdepasse+l10";  // Exemple de commande MODE IRC
    processModeCommand(modeCommand, userMode, password, userLimit);

    // Afficher le résultat
    std::cout << "User Mode après la commande : " << userMode << std::endl;
    std::cout << "Mot de passe : " << password << std::endl;
    std::cout << "Limite d'utilisateurs : " << userLimit << std::endl;

    return 0;
}

*/