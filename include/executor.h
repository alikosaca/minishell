/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:43:22 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/11 00:34:10 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <readline/readline.h>

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "structs.h"
# include "utils.h"
# include "signal.h"
# include "builtin.h"

# define PS2 "> "
# define ERR_CMD_NOT_FOUND "command not found"

int			executor(t_shell *shell, t_cmd *cmd);

int			is_builtin(char *cmd);
int			exec_builtin(t_shell *shell, t_cmd *cmd);

int			exec_external(t_shell *shell, t_cmd *cmd);
int			is_external(t_shell *shell, char *cmd);

char		*find_cmd_path(t_shell *shell, char *cmd);

int			setup_redir(t_shell *shell, t_cmd *cmd);

int			restore_std_fds(t_shell *shell);
int 		restore_doc_fds(t_shell *shell, int fd[2], bool should_dup);

int			is_it_over(t_redirect *redir, int fd[2], char *line);
void		print_line(int fd[2], char *line, char *expanded_line);
char		*should_be_expand(t_redirect *redir, char *line);

t_redirect	*get_last_redir(t_redirect *redir);

#endif
