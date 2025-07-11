NAME		= philo
CC			= cc
CFLAGS		= -Werror -Wall -Wextra -pthread

# ? Run 'make re MODE=pretty' for color formatting (no debug or ASAN).
# ? Run 'make re MODE=debug' for debug and ASAN.
# ! Note: SAN will not work with valgrind

MODE		= none
ifeq ($(MODE), pretty)
	CFLAGS	+= -D DEBUG_FORMATTING=1
endif
ifeq ($(MODE), debug)
	CFLAGS	+= -D DEBUG_FORMATTING=1 -fsanitize=thread -fsanitize=address \
		-fsanitize=leak -fsanitize=undefined -g
endif

SRC_PATH	= src/
OBJ_PATH	= obj/

SRC		=	main.c utils.c ft_atoi.c

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