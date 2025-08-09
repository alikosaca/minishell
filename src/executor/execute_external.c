/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:15:22 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/09 15:00:07 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

static void	child_exec_error(t_shell *shell, char *path, char **envp)
{
	if (errno == EACCES || errno == ENOEXEC)
		cmd_err(shell, path, strerror(errno), 126);
	else if (errno == ENOENT)
		cmd_err(shell, path, strerror(errno), 127);
	_free(&path);
	__free(&envp);
	cleanup(shell);
	exit(shell->exitcode);
}

static void	child(t_shell *shell, t_cmd *cmd)
{
	char		*path;
	char		**envp;
	struct stat	st;

	path = find_cmd_path(shell, cmd->argv[0]);
	if (!path || !ft_strcmp(cmd->argv[0], ".."))
	{
		cmd_err(shell, cmd->argv[0], ERR_CMD_NOT_FOUND, 127);
		cleanup(shell);
		exit(shell->exitcode);
	}
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		cmd_err(shell, cmd->argv[0], ERR_IS_A_DIR, 126);
		_free(&path);
		cleanup(shell);
		exit(shell->exitcode);
	}
	envp = env_to_arr(shell->envlist);
	execve(path, cmd->argv, envp);
	child_exec_error(shell, path, envp);
}

static int	parent(pid_t pid)
{
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

int	exec_external(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;

	if (!ft_strcmp(cmd->argv[0], "."))
		return (2);
	pid = fork();
	if (pid == -1)
		return (cmd_err(shell, "fork", strerror(errno), 254));
	else if (pid == 0)
		child(shell, cmd);
	return (parent(pid));
}
