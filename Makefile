# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 00:00:00 by yaycicek          #+#    #+#              #
#    Updated: 2025/08/07 15:06:40 by yaycicek         ###   ########.fr        #
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
               $(SRC_DIR)/init.c
LEXER_SRC    = \
               $(LEXER_DIR)/lexer.c \
               $(LEXER_DIR)/lexer_utils.c \
               $(LEXER_DIR)/token.c \
               $(LEXER_DIR)/token_handlers.c \
               $(LEXER_DIR)/token_process.c \
               $(LEXER_DIR)/syntax.c
EXPAND_SRC   = \
               $(EXPAND_DIR)/expansion.c \
               $(EXPAND_DIR)/expansion_utils.c \
               $(EXPAND_DIR)/merge.c \
               $(EXPAND_DIR)/expansion_proccess.c
PARSER_SRC   = \
	           $(PARSER_DIR)/parser.c \
               $(PARSER_DIR)/parser_utils.c \
               $(PARSER_DIR)/cmd.c \
               $(PARSER_DIR)/cmd_utils.c
EXECUTOR_SRC = \
               $(EXECUTOR_DIR)/executor.c \
               $(EXECUTOR_DIR)/execute_builtin.c \
               $(EXECUTOR_DIR)/execute_external.c \
               $(EXECUTOR_DIR)/external_utils.c \
               $(EXECUTOR_DIR)/redirections.c \
               $(EXECUTOR_DIR)/restore.c \
               $(EXECUTOR_DIR)/heredoc_utils.c \
               $(EXECUTOR_DIR)/pipeline.c
ENV_SRC      = \
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
               $(SIGNAL_DIR)/signal.c
UTILS_SRC    = \
               $(UTILS_DIR)/error.c \
               $(UTILS_DIR)/free.c \
               $(UTILS_DIR)/cleanup.c

SRCS         = $(MAIN_SRC) $(LEXER_SRC) $(EXPAND_SRC) $(PARSER_SRC) $(EXECUTOR_SRC) \
               $(ENV_SRC) $(BUILTIN_SRC) $(SIGNAL_SRC) $(UTILS_SRC)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(READLINE) -o $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

term:
	valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--track-fds=yes \
	--trace-children=yes \
	--suppressions=readline.supp \
	./minishell

log:
	valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--track-fds=yes \
	--trace-children=yes \
	--suppressions=readline.supp \
	--log-file="valgrind.log" \
	./minishell

.PHONY: all clean fclean re term log
