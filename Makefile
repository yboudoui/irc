# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/12 12:46:16 by yboudoui          #+#    #+#              #
#    Updated: 2023/12/26 18:08:41 by yboudoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	webserve

#-----------------------------------------------------------------------------#

SRCS				=	main.cpp\
						srcs/Message.cpp \
						srcs/MessageQueue.cpp \
						srcs/responses.cpp \
						srcs/User.cpp \
						srcs/Wagner.cpp \
						srcs/Wagner_connection.cpp \
						srcs/Wagner_mode.cpp \
						srcs/Wagner_kick.cpp \
						srcs/Wagner_invite.cpp \
						srcs/Wagner_topic.cpp \
						srcs/Wagner_whois.cpp \
						srcs/Wagner_quit.cpp \
						srcs/Wagner_privmsg.cpp \
						srcs/Wagner_join.cpp \
						srcs/Wagner_ping.cpp \
						srcs/Channel.cpp \
						srcs/Queue.cpp \
						srcs/IQueueEventListener.cpp \
						srcs/SocketBind.cpp \
						srcs/SocketConnection.cpp \
						srcs/extractor.cpp \
						srcs/responses/ERR_ALREADYREGISTERED.cpp \
						srcs/responses/ERR_BADCHANNELKEY.cpp \
						srcs/responses/ERR_BANNEDFROMCHAN.cpp \
						srcs/responses/ERR_CANNOTSENDTOCHAN.cpp \
						srcs/responses/ERR_CHANNELISFULL.cpp \
						srcs/responses/ERR_CHANOPRIVSNEEDED.cpp \
						srcs/responses/ERR_ERRONEUSNICKNAME.cpp \
						srcs/responses/ERR_INVITEONLYCHAN.cpp \
						srcs/responses/ERR_KEYSET.cpp \
						srcs/responses/ERR_NEEDMOREPARAMS.cpp \
						srcs/responses/ERR_NICKNAMEINUSE.cpp \
						srcs/responses/ERR_NONICKNAMEGIVEN.cpp \
						srcs/responses/ERR_NORECIPIENT.cpp \
						srcs/responses/ERR_NOSUCHCHANNEL.cpp \
						srcs/responses/ERR_NOSUCHNICK.cpp \
						srcs/responses/ERR_NOTEXTTOSEND.cpp \
						srcs/responses/ERR_NOTONCHANNEL.cpp \
						srcs/responses/ERR_PASSWDMISMATCH.cpp \
						srcs/responses/ERR_TOOMANYTARGETS.cpp \
						srcs/responses/ERR_UMODEUNKNOWNFLAG.cpp \
						srcs/responses/ERR_UNKNOWNMODE.cpp \
						srcs/responses/ERR_USERONCHANNEL.cpp \
						srcs/responses/PONG.cpp \
						srcs/responses/PRIVMSG.cpp \
						srcs/responses/RPL_CHANNELMODEIS.cpp \
						srcs/responses/RPL_CREATED.cpp \
						srcs/responses/RPL_INVITING.cpp \
						srcs/responses/RPL_MYINFO.cpp \
						srcs/responses/RPL_NAMREPLY.cpp \
						srcs/responses/RPL_NOTOPIC.cpp \
						srcs/responses/RPL_TOPIC.cpp \
						srcs/responses/RPL_WELCOME.cpp \
						srcs/responses/RPL_WHOISUSER.cpp \
						srcs/responses/RPL_YOURHOST.cpp


INCS				=	./incs \

OBJS_DIR			=	./objs

OBJS				:=	$(SRCS:%.cpp=$(OBJS_DIR)/%.o)

DEPS				:=	$(OBJS:%.o=%.d)

#-----------------------------------------------------------------------------#

CXX					=	clang++

CXXFLAGS			=	-Wall -Wextra -Werror -MMD -std=c++98 -g3 -DDEBUG# -fsanitize=address

RM					=	rm -f

$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(addprefix -I, $(INCS)) -c $< -o $@

$(NAME):	$(OBJS)
	$(CXX) $(CXXFLAGS) $(addprefix -I, $(INCS)) $(OBJS) -o $(NAME) $(LIBS)

all:		$(NAME)

clean:
	$(RM) -r $(OBJS_DIR)

fclean:		clean
	$(RM) $(NAME)
	$(RM) -r $(PATH_BUILD)
	$(RM) -r $(PATH_LIB)

re:			fclean
	make all

.PHONY:		all clean fclean re
