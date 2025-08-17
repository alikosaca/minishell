/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:43:22 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/17 17:02:52 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <readline/readline.h>

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include "structs.h"
# include "utils.h"
# include "expansion.h"
# include "builtin.h"
# include "sig.h"

# define PS2 "> "

# define ERR_CMD_NOT_FOUND "command not found"
# define ERR_IS_A_DIR "Is a directory"
# define ERR_FILENAME_REQUIRED "filename argument required"
# define ERR_DOT_SYNTAX ". filename [arguments]"

int			executor(t_shell *shell, t_cmd *cmd);
int			exec_cmd(t_shell *shell, t_cmd *cmd);

int			setup_redir(t_shell *shell, t_cmd *cmd);
int			prepare_heredocs_for_cmd(t_shell *shell, t_redirect *redir);

void		c_heredoc(t_shell *shell, t_redirect *redir, int fd[2]);
int			p_heredoc(t_shell *shell, pid_t pid, int fd[2]);
int			is_it_over(t_redirect *redir, char *line);
void		should_be_expand(t_shell *shell, t_redirect *redir, char **line);
void		print_line(int fd[2], char *line);

int			redir_in(t_shell *shell, t_redirect *redir);
int			redir_out(t_shell *shell, t_redirect *redir);
int			redir_append(t_shell *shell, t_redirect *redir);

int			is_builtin(t_cmd *cmd);
int			exec_builtin(t_shell *shell, t_cmd *cmd);

int			exec_external(t_shell *shell, t_cmd *cmd);
char		*find_cmd_path(t_shell *shell, char *cmd);
void		validate_cmd_path(t_shell *shell, t_cmd *cmd, char *path);

int			exec_pipeline(t_shell *shell, t_cmd *cmd);
pid_t		create_process(t_shell *shell, t_cmd *cmd, int pipefd[2]);
void		wait_all_children(t_shell *shell, pid_t *pids, int child_count);

int			restore_std_fds(t_shell *shell);

#endif
