# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 00:00:00 by yaycicek          #+#    #+#              #
#    Updated: 2025/07/11 19:57:04 by yaycicek         ###   ########.fr        #
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

LEXER_DIR    = $(SRC_DIR)/lexer
EXPAND_DIR   = $(SRC_DIR)/expansion
PARSER_DIR   = $(SRC_DIR)/parser
EXECUTOR_DIR = $(SRC_DIR)/executor
ENV_DIR      = $(SRC_DIR)/env
BUILTIN_DIR  = $(SRC_DIR)/builtin
SIGNAL_DIR   = $(SRC_DIR)/signal
UTILS_DIR    = $(SRC_DIR)/utils

MAIN_SRC     = $(SRC_DIR)/main.c \
               $(SRC_DIR)/init.c \
               $(SRC_DIR)/cleanup.c
LEXER_SRC    = \
				$(LEXER_DIR)/lexer.c \
				$(LEXER_DIR)/lexer_utils.c \
				$(LEXER_DIR)/token.c \
				$(LEXER_DIR)/token_handlers.c \
				$(LEXER_DIR)/token_process.c \
				$(LEXER_DIR)/syntax.c
EXPAND_SRC   = \
               $(EXPAND_DIR)/expansion.c \
               $(EXPAND_DIR)/expansion_utils.c
PARSER_SRC   = \
	            $(PARSER_DIR)/parser.c \
               $(PARSER_DIR)/parser_utils.c \
               $(PARSER_DIR)/cmd.c
EXECUTOR_SRC = \
               $(EXECUTOR_DIR)/executor.c \
               $(EXECUTOR_DIR)/execute_builtin.c \
               $(EXECUTOR_DIR)/execute_external.c \
               $(EXECUTOR_DIR)/external_utils.c \
               $(EXECUTOR_DIR)/redirections.c \
               $(EXECUTOR_DIR)/restore.c \
               $(EXECUTOR_DIR)/heredoc_utils.c \
               $(EXECUTOR_DIR)/pipeline.c
ENV_SRC	     = \
               $(ENV_DIR)/env_init.c \
               $(ENV_DIR)/env_utils.c \
               $(ENV_DIR)/env_convert.c \
               $(ENV_DIR)/env.c
BUILTIN_SRC  = \
               $(BUILTIN_DIR)/builtin_echo.c \
               $(BUILTIN_DIR)/builtin_cd.c \
               $(BUILTIN_DIR)/builtin_pwd.c \
               $(BUILTIN_DIR)/builtin_export.c \
               $(BUILTIN_DIR)/builtin_unset.c \
               $(BUILTIN_DIR)/builtin_exit.c
SIGNAL_SRC   = \
            #    $(SIGNAL_DIR)/signals.c \
            #    $(SIGNAL_DIR)/handle_signals.c
UTILS_SRC    = \
               $(UTILS_DIR)/error.c \

MAIN_OBJ     = $(MAIN_SRC:.c=.o)
LEXER_OBJ    = $(LEXER_SRC:.c=.o)
EXPAND_OBJ   = $(EXPAND_SRC:.c=.o)
PARSER_OBJ   = $(PARSER_SRC:.c=.o)
EXECUTOR_OBJ = $(EXECUTOR_SRC:.c=.o)
ENV_OBJ	     = $(ENV_SRC:.c=.o)
BUILTIN_OBJ  = $(BUILTIN_SRC:.c=.o)
SIGNAL_OBJ   = $(SIGNAL_SRC:.c=.o)
UTILS_OBJ    = $(UTILS_SRC:.c=.o)

SRCS         = $(MAIN_SRC) $(LEXER_SRC) $(EXPAND_SRC) $(PARSER_SRC) $(EXECUTOR_SRC) \
               $(ENV_SRC) $(BUILTIN_SRC) $(SIGNAL_SRC) $(UTILS_SRC)
# ----------------------------------------------------------------------- #
OBJS         = $(MAIN_OBJ) $(LEXER_OBJ) $(EXPAND_OBJ) $(PARSER_OBJ) $(EXECUTOR_OBJ) \
               $(ENV_OBJ) $(BUILTIN_OBJ) $(SIGNAL_OBJ) $(UTILS_OBJ)

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

val:
	valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--track-fds=yes \
	--trace-children=yes \
	--child-silent-after-fork=yes \
	./minishell

val2:
	valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--track-fds=yes \
	--trace-children=yes \
	--child-silent-after-fork=yes \
	--log-file="/home/yaycicek/Desktop/minishell/valgrind.log" \
	./minishell

a:
	./minishell

.PHONY: all clean fclean re
