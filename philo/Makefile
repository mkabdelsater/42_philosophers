# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moabdels <moabdels@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/06 14:56:36 by moabdels          #+#    #+#              #
#    Updated: 2025/08/06 14:56:37 by moabdels         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
CC			= cc
DEBUG		= -fsanitize=thread -fsanitize=address -fsanitize=leak \
				-fsanitize=undefined -g

CFLAGS		= -Werror -Wall -Wextra -pthread

SRC_PATH	= src/
OBJ_PATH	= obj/

SRC		=	main.c utils.c ft_atoi.c setup.c cleanup.c conclude.c reporting.c \
			routines.c
SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

INC		= -I ./inc/

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean