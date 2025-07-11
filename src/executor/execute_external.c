/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:15:22 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/11 20:58:25 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

static int	child(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	char	**envp;

	path = find_cmd_path(shell, cmd->argv[0]);
	if (!path)
		return (1);
	envp = env_to_arr(shell->envlist);
	if (!envp)
		return (1);
	execve(path, cmd->argv, envp);
	if (errno == EACCES || errno == ENOEXEC)
		return (cmd_err(shell, NULL, strerror(errno), 126));
	else if (errno == ENOENT)
		return (cmd_err(shell, NULL, strerror(errno), 127));
	return (0);
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

	if (!cmd || !cmd->argv)
		return (0);
	path = find_cmd_path(shell, cmd->argv[0]);
	if (!path)
	{
		cmd_err(shell, cmd->argv[0], ERR_CMD_NOT_FOUND, 127);
		return (0);
	}
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
