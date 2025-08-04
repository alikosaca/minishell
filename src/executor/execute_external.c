/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:15:22 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/04 19:01:30 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"
#include <sys/stat.h>

static int	child(t_shell *shell, t_cmd *cmd)
{
    char		*path;
    char		**envp;
    struct stat	st;

    path = NULL;
    path = find_cmd_path(shell, cmd->argv[0]);
    if (!path)
        exit(cmd_err(shell, cmd->argv[0], ERR_CMD_NOT_FOUND, 127));
    if (stat(path, &st) == 0)
        if (S_ISDIR(st.st_mode))
		{
			_free(&path);
            exit(cmd_err(shell, cmd->argv[0], ERR_IS_A_DIR, 126));
		}
    envp = env_to_arr(shell->envlist);
    if (!envp)
        exit(1);
    execve(path, cmd->argv, envp);
	_free(&path);
    if (errno == EACCES || errno == ENOEXEC)
        exit(cmd_err(shell, cmd->argv[0], strerror(errno), 126));
    else if (errno == ENOENT)
        exit(cmd_err(shell, cmd->argv[0], strerror(errno), 127));
    exit(cmd_err(shell, cmd->argv[0], strerror(errno), shell->exitcode));
}

static int	parent(t_shell *shell, pid_t pid)
{
	(void)shell;
	int	status;

	status = 0;
	if (waitpid(pid, &status, 0) == -1)
		return (1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	is_external(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	if (!cmd || !cmd->argv || !cmd->argv[0]
		|| ft_strcmp(cmd->argv[0], ".") == 0
		|| ft_strcmp(cmd->argv[0], "..") == 0)
		return (0);
	path = find_cmd_path(shell, cmd->argv[0]);
	if (!path)
	{
		cmd_err(shell, cmd->argv[0], ERR_CMD_NOT_FOUND, 127);
		return (0);
	}
	_free(&path);
	return (1);
}

int	exec_external(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (cmd_err(shell, "fork", strerror(errno), 254));
	else if (pid == 0)
		return (child(shell, cmd));
	return (parent(shell, pid));
}
