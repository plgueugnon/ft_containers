# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/21 14:58:12 by pgueugno          #+#    #+#              #
#    Updated: 2021/12/27 21:26:23 by pgueugno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                               Filename output                                #
################################################################################

NAME		=	program

################################################################################
#                         Sources and objects directories                      #
################################################################################

SRCS_DIR	=	.
FT_DIR		=	srcs
OBJS_DIR	=	objs
LIBFT_MAKE	=	Makefile
TESTS_DIR	=	test

################################################################################
#                               Sources filenames                              #
################################################################################

SRCS		=	main.cpp

################################################################################
#                              Commands and arguments                          #
################################################################################

CXX				=	clang++
HEADERS			=	$(FT_DIR) $(TESTS_DIR)
INCLUDE			=	$(HEADERS:%=-I%)
DEBUG			=	-fsanitize=address
CXXFLAGS		=	-Wall -Wextra -Werror -g3 -std=c++98 $(INCLUDE) $(DEBUG)
RM				=	rm -f

################################################################################
#                                 Defining colors                              #
################################################################################

_RED		=	\033[31m
_GREEN		=	\033[32m
_YELLOW		=	\033[33m
_CYAN		=	\033[96m
_NC			=	\033[0m

################################################################################
#                                  Compiling                                   #
################################################################################

OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))

all:	init $(NAME)

init:
		@ if test -f $(NAME);\
		then echo "$(_CYAN)[program already created]$(_NC)";\
		else echo "$(_YELLOW)[Initialize program]$(_NC)";\
		fi
		$(shell mkdir -p $(OBJS_DIR))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
				@ echo "\t$(_YELLOW) compiling... $*.cpp$(_NC)"
				$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			@ echo "\t$(_YELLOW)[Creating program]$(_NC)"
			$(CXX) $(OBJS) -o $(NAME) $(DEBUG)
			@ echo "$(_GREEN)[program created & ready]$(_NC)"

clean:
		@ echo "$(_RED)[cleaning up .out & objects files]$(_NC)"
		$(RM) $(OBJS)

fclean: clean
		@ echo "$(_RED)[cleaning up .out, objects & library files]$(_NC)"
		$(RM) $(NAME)

re:	fclean all

.SILENT:
		all
.PHONY: all clean fclean re bonus
