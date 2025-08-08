/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:55:37 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/08 12:46:58 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

static int	wait_all_children(t_shell *shell, pid_t *pids, int child_count)
{
	int	status;
	int	i;

	i = 0;
	while (i < child_count)
	{
		printf("child: %d\n", pids[i]);
		if (waitpid(pids[i], &status, 0) == -1)
			break ;
		if (child_count - 1 == i)
		{
			printf("last child: %d\n", pids[i]);
			if (WIFEXITED(status))
					shell->exitcode = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					shell->exitcode = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (shell->exitcode);
}

static void	child(t_shell *shell, t_cmd *cmd, int in_fd, int pipefd[2])
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (cmd->next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	if (is_builtin(cmd))
		shell->exitcode = exec_builtin(shell, cmd);
	else
		shell->exitcode = exec_external(shell, cmd);
	cleanup(shell);
	exit(shell->exitcode);
}

static int	parent(int in_fd, int pipefd[2], t_cmd *cmd)
{
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
		return (pipefd[0]);
	}
	return (STDIN_FILENO);
}

int	exec_pipeline(t_shell *shell, t_cmd *cmd)
{
	int		pipefd[2];
	int		in_fd;
	int		child_count;
	pid_t	pid;
	pid_t	pids[30898];

	child_count = 0;
	in_fd = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->next && pipe(pipefd) == -1)
			return (cmd_err(shell, "pipe", strerror(errno), 1));
		pid = fork();
		if (pid == -1)
			return (cmd_err(shell, "fork", strerror(errno), 1));
		if (pid == 0)
			child(shell, cmd, in_fd, pipefd);
		pids[child_count] = pid;
		in_fd = parent(in_fd, pipefd, cmd);
		child_count++;
		cmd = cmd->next;
	}
	return (wait_all_children(shell, pids, child_count));
}
