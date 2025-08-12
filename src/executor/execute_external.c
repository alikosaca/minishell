/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:15:22 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/12 15:25:23 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

static void	execute_cmd(t_shell *shell, char *path, char **argv, char **envp)
{
	execve(path, argv, envp);
	_free((void **)&path);
	__free((void ***)&envp);
	cleanup(shell);
	exit(shell->exitcode);
}

static void	child(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	char	**envp;

	path = NULL;
	envp = NULL;
	signal(SIGINT, SIG_DFL);
	if (setup_redir(shell, cmd))
	{
		cleanup(shell);
		exit(shell->exitcode);
	}
	path = find_cmd_path(shell, cmd->argv[0]);
	validate_cmd_path(shell, cmd, path);
	envp = env_to_arr(shell->envlist);
	execute_cmd(shell, path, cmd->argv, envp);
}

static int	parent(pid_t pid)
{
	int	status;

	status = 0;
	if (waitpid(pid, &status, 0) == -1)
		return (1);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			printf("\n");
		interactive_signals();
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
	{
		interactive_signals();
		return (WEXITSTATUS(status));
	}
	interactive_signals();
	return (0);
}

int	exec_external(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	if (!ft_strcmp(cmd->argv[0], "."))
		return (2);
	pid = fork();
	if (pid == -1)
		return (cmd_err(shell, "fork", strerror(errno), 254));
	else if (pid == 0)
		child(shell, cmd);
	return (parent(pid));
}
