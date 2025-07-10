/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:26:26 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/10 17:33:26 by akosaca          ###   ########.fr       */
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
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redirect_type;

typedef struct s_redirect
{
	t_redirect_type		type;
	char				*file;
	char				*delimiter;
	bool				should_be_expand;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd
{
	char				**argv;
	t_redirect			*redirects;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_arglist
{
	char	**argv;
	int		argc;
}	t_arglist;


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
	bool		in_heredoc;
	int			stdin_backup;
	int			stdout_backup;
}	t_shell;

#endif
