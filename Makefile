# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/14 12:49:23 by hyap              #+#    #+#              #
#    Updated: 2022/12/28 17:56:29 by hyap             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= main
SRCSDIR		= srcs
SRCS		= $(wildcard $(SRCSDIR)/*.cpp)
OBJSDIR		= srcs/obj
OBJS 		= $(SRCS:$(SRCSDIR)/%.cpp=$(OBJSDIR)/%.o)
DEPENDSDIR	= srcs/depends
DEPENDS		= $(SRCS:$(SRCSDIR)/%.cpp=$(DEPENDSDIR)/%.d)
CPPFLAGS	= -Wall -Werror -Wextra -Wshadow -std=c++98 -pedantic -I includes/
DEPFLAGS	= -MM
LDFLAGS		= -g -lstdc++ #-fsanitize=address
TPP			= $(wildcard $(SRCSDIR)/*.tpp)
HPP			= $(wildcard includes/*.hpp)


all: $(NAME)

$(NAME): $(OBJS)
	gcc $(LDFLAGS) $< -o $(NAME)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.cpp $(TPP) $(HPP) | $(OBJSDIR)
	gcc $(CPPFLAGS) -c $< -o $@

$(DEPENDSDIR)/%.d: $(SRCSDIR)/%.cpp | $(DEPENDSDIR)
	c++ $(CPPFLAGS) $(DEPFLAGS) $< -o $@

$(OBJSDIR) $(DEPENDSDIR):
	mkdir -p $@

-include $(DEPENDS)

clean:
	$(RM) -rv $(OBJSDIR) $(DEPENDSDIR)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
