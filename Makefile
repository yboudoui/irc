# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/12 12:46:16 by yboudoui          #+#    #+#              #
#    Updated: 2024/01/03 17:27:45 by yboudoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	ircserv

#-----------------------------------------------------------------------------#

SRCS_RESPONSES		= \
					ERR_ALREADYREGISTERED.cpp \
					ERR_BADCHANNELKEY.cpp \
					ERR_BANNEDFROMCHAN.cpp \
					ERR_CANNOTSENDTOCHAN.cpp \
					ERR_CHANNELISFULL.cpp \
					ERR_CHANOPRIVSNEEDED.cpp \
					ERR_ERRONEUSNICKNAME.cpp \
					ERR_INVITEONLYCHAN.cpp \
					ERR_KEYSET.cpp \
					ERR_NEEDMOREPARAMS.cpp \
					ERR_NICKNAMEINUSE.cpp \
					ERR_NONICKNAMEGIVEN.cpp \
					ERR_NORECIPIENT.cpp \
					ERR_NOSUCHCHANNEL.cpp \
					ERR_NOSUCHNICK.cpp \
					ERR_NOTEXTTOSEND.cpp \
					ERR_NOTONCHANNEL.cpp \
					ERR_PASSWDMISMATCH.cpp \
					ERR_TOOMANYTARGETS.cpp \
					ERR_UMODEUNKNOWNFLAG.cpp \
					ERR_UNKNOWNMODE.cpp \
					ERR_USERONCHANNEL.cpp \
					JOIN.cpp \
					KICK.cpp \
					PONG.cpp \
					PRIVMSG.cpp \
					RPL_CHANNELMODEIS.cpp \
					RPL_CREATED.cpp \
					RPL_INVITING.cpp \
					RPL_MYINFO.cpp \
					RPL_NAMREPLY.cpp \
					RPL_NOTOPIC.cpp \
					RPL_TOPIC.cpp \
					RPL_WELCOME.cpp \
					RPL_WHOISUSER.cpp \
					RPL_YOURHOST.cpp

SRCS				= \
					signal_handler.cpp \
					Message.cpp \
					MessageQueue.cpp \
					responses.cpp \
					User.cpp \
					Wagner.cpp \
					Wagner_connection.cpp \
					Wagner_mode.cpp \
					Wagner_kick.cpp \
					Wagner_invite.cpp \
					Wagner_topic.cpp \
					Wagner_whois.cpp \
					Wagner_quit.cpp \
					Wagner_privmsg.cpp \
					Wagner_join.cpp \
					Wagner_ping.cpp \
					Channel.cpp \
					Queue.cpp \
					IQueueEventListener.cpp \
					SocketBind.cpp \
					SocketConnection.cpp \
					extractor.cpp \
					$(addprefix responses/, ${SRCS_RESPONSES} )


SOURCES				=	main.cpp \
						$(addprefix srcs/, ${SRCS})


INCLUDES			=	./incs

OBJS_DIR			=	./objs

OBJECTS				:=	$(SOURCES:%.cpp=$(OBJS_DIR)/%.o)

DEPS				:=	$(OBJECTS:%.o=%.d)

#-----------------------------------------------------------------------------#

CXX					:=	c++

CXXFLAGS			+=	-Wall -Wextra -Werror -std=c++98

RM					=	rm -f

#-----------------------------------------------------------------------------#

$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(addprefix -I, $(INCLUDES)) -c $< -o $@

$(NAME):	$(OBJECTS)
	$(CXX) $(CXXFLAGS) $(addprefix -I, $(INCLUDES)) $(OBJECTS) -o $(NAME) $(LIBS)

#-----------------------------------------------------------------------------#

all:	$(NAME)

clean:
	$(RM) -r $(OBJS_DIR)

fclean:	clean
	$(RM) $(NAME)
	$(RM) -r $(PATH_BUILD)
	$(RM) -r $(PATH_LIB)

re:	fclean all

#-----------------------------------------------------------------------------#

port			= 8080
password		= password

VALGRIND_PARAMS	+=	--track-fds=yes
VALGRIND_PARAMS	+=	--leak-check=full
VALGRIND_PARAMS	+=	--show-leak-kinds=all

test: CXXFLAGS += -g3 -DDEBUG
test: re
	valgrind -q \
		${VALGRIND_PARAMS} \
		./${NAME} \
		${port} ${password}

#-----------------------------------------------------------------------------#

.PHONY:		all clean fclean re
