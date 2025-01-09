# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/07 12:51:30 by okrahl            #+#    #+#              #
#    Updated: 2025/01/07 12:51:31 by okrahl           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= btc
CC			= c++
CFLAGS		= -Wall -Wextra -Werror -std=c++98

SRC_DIR		= src/
OBJ_DIR		= obj/
INCL_DIR	= incl/

SRCS		= main.cpp \
			  BitcoinExchange.cpp

OBJS		= $(addprefix $(OBJ_DIR), $(SRCS:.cpp=.o))
DEPS		= $(INCL_DIR)BitcoinExchange.hpp

all:		$(OBJ_DIR) $(NAME)

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp $(DEPS)
			$(CC) $(CFLAGS) -I$(INCL_DIR) -c $< -o $@

clean:
			rm -rf $(OBJ_DIR)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
