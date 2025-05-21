NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -Llibft -lft
INCLUDES = -Iinclude -Ilibft

RM = rm -rf

SRC = # minishell source files here
OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ)
	make -C libft clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
