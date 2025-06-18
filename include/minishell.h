/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:46:03 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/18 07:03:26 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <aio.h> // for pid_t

# include "env.h"
# include "builtin.h"
# include "signal.h"
# include "utils.h"
# include "lexer.h"
# include "parser.h"

typedef struct s_shell
{
	char		*prompt;
	char		*input;
	t_env		*envlist;
	t_token		*tokens;
	t_command	*commands;
	int			exit_status;
	int			last_exit_code;
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
