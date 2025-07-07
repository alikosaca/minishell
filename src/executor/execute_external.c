/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:15:22 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/07 22:01:29 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

static int	child(t_shell *shell, t_cmd *cmd, char *path)
{
	char	**envp;

	envp = env_to_arr(shell->envlist);
	if (!envp)
		return (1); // ? should be '1' ?
	execve(path, cmd->argv, envp);
	if (errno == EACCES)
		return (cmd_err(shell, NULL, strerror(errno), 126));
	else if (errno == ENOEXEC)
		return (cmd_err(shell, NULL, strerror(errno), 126));
	else if (errno == ENOENT)
		return (cmd_err(shell, NULL, strerror(errno), 127));
	return (0);
}

static int	parent(t_shell *shell, pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (shell->exitcode);
}

int	exec_external(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	char	*path;

	path = find_cmd_path(shell, cmd->argv[0]);
	if (!path)
		return (cmd_err(shell, cmd->argv[0], ERR_CMD_NOT_FOUND, 127));
	pid = fork();
	if (pid == -1)
		return (cmd_err(shell, "fork", strerror(errno), 254));
	else if (pid == 0)
	{
		if (setup_redir(shell, cmd))
			return (cmd_err(shell, NULL, NULL, 1));
		return (child(shell, cmd, path));
	}
	free(path);
	return (parent(shell, pid));
}
