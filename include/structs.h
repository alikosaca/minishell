/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:26:26 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/05 19:19:40 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <fcntl.h>
# include <stdbool.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	bool			exported;
	struct s_env	*next;
}	t_env;

typedef enum e_token_type
{
	T_WORD,
	T_SINGLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_REDIRECT_APPEND,
	T_HEREDOC,
	T_PIPE,
	T_DOLLAR,
	T_ERROR			
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef enum e_redirect_type
{
	REDIR_IN,                      // <
	REDIR_OUT,                     // >
	REDIR_APPEND,                  // >>
	REDIR_HEREDOC                  // <<
}	t_redirect_type;

typedef struct s_redirect
{
	t_redirect_type		type;         // redirection tipi
	char				*file;        // hedef dosya adı
	char				*delimiter;   // heredoc delimiter
	bool				should_be_expand;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd
{
	char				**argv;       // execve için argüman listesi (with NULL terminated)
	t_redirect			*redirects;   // redirection listesi (last arg: NULL)
	struct s_cmd		*next;        // pipe varsa bir sonraki komuta
}	t_cmd;

typedef struct s_shell
{
	char		*prompt;
	char		*input;
	t_env		*envlist;
	t_token		*tokens;
	t_cmd		*commands;
	int			exitstat;
	int			exitcode;
	pid_t		*pids;
	int			pid_count;
	int			signal_received;
	int			in_execution;
	int			in_heredoc;
	int			stdin_backup;
	int			stdout_backup;
	int			syntax_error;
}	t_shell;

#endif
