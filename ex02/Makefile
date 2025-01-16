# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/07 12:51:30 by okrahl            #+#    #+#              #
#    Updated: 2025/01/16 12:56:41 by okrahl           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= PmergeMe
CC			= c++
CFLAGS		= -Wall -Wextra -Werror -std=c++98

DEBUG		= 0


ifeq ($(DEBUG),1)
	CFLAGS += -D DEBUG_MODE
endif

SRC_DIR		= src/
OBJ_DIR		= obj/

SRCS		= main.cpp \
			  PmergeMe.cpp

OBJS		= $(addprefix $(OBJ_DIR), $(SRCS:.cpp=.o))

all:		$(OBJ_DIR) $(NAME)

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			rm -rf $(OBJ_DIR)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
