/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:55:37 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/09 19:19:38 by yaycicek         ###   ########.fr       */
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
		if (waitpid(pids[i], &status, 0) == -1)
			break ;
		if (child_count - 1 == i)
		{
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					printf("\n");
				shell->exitcode = 128 + WTERMSIG(status);
			}
			else if (WIFEXITED(status))
				shell->exitcode = WEXITSTATUS(status);
		}
		i++;
	}
	return (shell->exitcode);
}

static void	child(t_shell *shell, t_cmd *cmd, int in_fd, int pipefd[2])
{
	signal(SIGINT, SIG_DFL);
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
	if (cmd->argv)
	{
		if (is_builtin(cmd))
			shell->exitcode = exec_builtin(shell, cmd);
		else
			shell->exitcode = exec_external(shell, cmd);
	}
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

static pid_t	create_process(t_shell *shell, t_cmd *cmd, int pipefd[2])
{
	pid_t	pid;

	if (cmd->next && pipe(pipefd) == -1)
	{
		cmd_err(shell, "pipe", strerror(errno), 1);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		cmd_err(shell, "fork", strerror(errno), 1);
		return (-1);
	}
	return (pid);
}

int	exec_pipeline(t_shell *shell, t_cmd *cmd)
{
	int		pipefd[2];
	int		in_fd;
	int		child_count;
	pid_t	pid;
	pid_t	pids[30898];

	signal(SIGINT, SIG_IGN);
	child_count = 0;
	in_fd = STDIN_FILENO;
	while (cmd)
	{
		pid = create_process(shell, cmd, pipefd);
		if (pid == -1)
			return (1);
		if (pid == 0)
			child(shell, cmd, in_fd, pipefd);
		pids[child_count++] = pid;
		in_fd = parent(in_fd, pipefd, cmd);
		cmd = cmd->next;
	}
	wait_all_children(shell, pids, child_count);
	interactive_signals();
	return (shell->exitcode);
}
