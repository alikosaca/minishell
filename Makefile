# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 00:00:00 by yaycicek          #+#    #+#              #
#    Updated: 2025/06/09 20:03:32 by yaycicek         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME         = minishell

CC           = cc
CFLAGS       = -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(LIBFT_DIR)
READLINE     = -lreadline
RM           = rm -f

INC_DIR      = include
SRC_DIR      = src
LIBFT_DIR    = libft

LIBFT        = $(LIBFT_DIR)/libft.a


MAIN_SRC     = $(SRC_DIR)/main.c
LEXER_DIR    = $(SRC_DIR)/lexer
PARSER_DIR   = $(SRC_DIR)/parser
EXECUTOR_DIR = $(SRC_DIR)/executor
ENV_DIR      = $(SRC_DIR)/env
BUILTIN_DIR  = $(SRC_DIR)/builtin
UTILS_DIR    = $(SRC_DIR)/utils

LEXER_SRC    = \
            #    $(LEXER_DIR)/lexer.c
PARSER_SRC   = \
            #    $(PARSER_DIR)/parser.c
EXECUTOR_SRC = \
            #    $(EXECUTOR_DIR)/executor.c
ENV_SRC	     = \
               $(ENV_DIR)/env_init.c \
               $(ENV_DIR)/env_utils.c \
               $(ENV_DIR)/env_convert.c \
               $(ENV_DIR)/env.c
BUILTIN_SRC  = \
               $(BUILTIN_DIR)/builtin_echo.c \
               $(BUILTIN_DIR)/builtin_cd.c
UTILS_SRC    = \
               $(UTILS_DIR)/error.c

MAIN_OBJ     = $(MAIN_SRC:.c=.o)
LEXER_OBJ    = $(LEXER_SRC:.c=.o)
PARSER_OBJ   = $(PARSER_SRC:.c=.o)
EXECUTOR_OBJ = $(EXECUTOR_SRC:.c=.o)
ENV_OBJ	     = $(ENV_SRC:.c=.o)
BUILTIN_OBJ  = $(BUILTIN_SRC:.c=.o)
UTILS_OBJ    = $(UTILS_SRC:.c=.o)

SRCS         = $(MAIN_SRC) $(LEXER_SRC) $(PARSER_SRC) $(EXECUTOR_SRC) \
               $(ENV_SRC) $(BUILTIN_SRC) $(UTILS_SRC)
# ----------------------------------------------------------------------- #
OBJS         = $(MAIN_OBJ) $(LEXER_OBJ) $(PARSER_OBJ) $(EXECUTOR_OBJ) \
               $(ENV_OBJ) $(BUILTIN_OBJ) $(UTILS_OBJ)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
