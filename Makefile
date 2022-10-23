# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/14 12:49:23 by hyap              #+#    #+#              #
#    Updated: 2022/10/23 16:11:58 by hyap             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= main
SRCSDIR		= srcs
SRCS		= $(wildcard $(SRCSDIR)/*.cpp)
OBJSDIR		= srcs/obj
OBJS 		= $(SRCS:$(SRCSDIR)/%.cpp=$(OBJSDIR)/%.o)
DEPENDSDIR	= srcs/depends
DEPENDS		= $(OBJS:$(OBJSDIR)/%.o=$(DEPENDSDIR)/%.d)
CPPFLAGS	= -Wall -Werror -Wextra -Wshadow -std=c++98 -pedantic -Iincludes
DEPFLAGS	= -MM -MT
LDFLAGS		= -lstdc++

all: $(NAME)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.cpp | $(DEPENDSDIR) $(OBJSDIR)
	c++ $(CPPFLAGS) -c $< -o $@
	c++ $(CPPFLAGS) $(DEPFLAGS) $@ $< -o $(DEPENDS)

$(NAME): $(OBJS)
	c++ $(LDFLAGS) $^ -o $@

$(OBJSDIR) $(DEPENDSDIR):
	@mkdir -p $@

-include $(DEPENDS)

clean:
	$(RM) -rv $(OBJSDIR) $(DEPENDSDIR) 

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
