# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obouhlel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/12 12:46:16 by yboudoui          #+#    #+#              #
#    Updated: 2023/12/04 11:36:22 by yboudoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	webserve

#-----------------------------------------------------------------------------#

SRCS				=	main.cpp\
						srcs/Queue.cpp \
						srcs/SocketBind.cpp \
						srcs/SocketConnection.cpp \
						srcs/Request.cpp\
						srcs/Response.cpp

INCS				=	./incs \

OBJS_DIR			=	./objs

OBJS				:=	$(SRCS:%.cpp=$(OBJS_DIR)/%.o)

DEPS				:=	$(OBJS:%.o=%.d)

#-----------------------------------------------------------------------------#

CXX					=	clang++

CXXFLAGS			=	-Wall -Wextra -Werror -MMD -std=c++98 -g3

RM					=	rm -f

$(OBJS_DIR)/%.o: %.cpp
	mkdir -p $(@D)
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
