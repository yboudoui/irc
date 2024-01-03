
		/* post-registration greeting
		Upon successful completion of the registration process,
		the server MUST send, in this order, 
			the RPL_WELCOME (001),
			RPL_YOURHOST (002),
			RPL_CREATED (003),
			RPL_MYINFO (004),
			and at least one RPL_ISUPPORT (005) numeric to the client. 
			
		The server SHOULD then respond as though the client sent the LUSERS
		command and return the appropriate numerics. If the user has client 
		modes set on them automatically upon joining the network, 
		
		the server SHOULD send the client 
			the RPL_UMODEIS (221) reply
			or a MODE message with the client as target,
		preferably the former.
		
		The server MAY send other numerics and messages.
		
		The server MUST then respond as though the client sent it the MOTD command,
		
		i.e. it must send either the successful Message of the Day numerics or the ERR_NOMOTD (422) numeric.


		
		RPL_WELCOME		(001) :Welcome to the Internet Relay Network <nick>!<user>@<host>
		RPL_YOURHOST	(002) :Your host is <servername>, running version <version> 
		RPL_CREATED		(003) :This server was created <date>
		RPL_MYINFO		(004) :<server_name> <version> <user_modes> <chan_modes> 
		RPL_ISUPPORT	(005)
		*/	


	/* ANNOUNCE ARRIVAL 
	SocketConnection*		_clientSocket;
	User*					_clientUser;

	Message	_clientOutput;
	_clientOutput.command.name = "PRIVMSG"; //433 ERR_NICKNAMEINUSE
	std::map<SocketConnection*,	User*>::iterator	it = _clients.begin();
	std::map<SocketConnection*,	User*>::iterator	ite = _clients.end();

	for ( ; it != ite ; it++)
	{
		if (_clientSocket != socket)
		{
		_clientSocket = it->first;
		_clientUser = it->second;

		_clientOutput.params.push_back(_clientUser->getNickname());
		_clientOutput.params.push_back(": A new user arrived on the server, say hello to " +_user->getNickname()+ "");	
		_clientSocket->insertResponse(_clientOutput);
		_clientOutput.params.clear();
		std::cout << ":A new user arrived : " << _clientUser->getNickname() << std::endl;
		}
	}
	*/






/*
nc -C 127.0.0.1 8080

RFC1459 (FR)
http://abcdrfc.free.fr/rfc-vf/rfc1459.html#23
RFC1459 (EN)
https://datatracker.ietf.org/doc/html/rfc1459#section-6
RETURN CODES 
https://www.alien.net.au/irc/irc2numerics.html

https://modern.ircdocs.horse/

QUESTIONS :
NB : les reponses sont toujours prefixees du nom du serveur 
	info a retrouver sur :
	http://chi.cs.uchicago.edu/chirc/irc.html#message-format
*/

