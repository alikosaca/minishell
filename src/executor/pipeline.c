/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:55:37 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/06 12:23:49 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

static int	wait_all_children(t_shell *shell, int child_count)
{
	int	status;
	int	i;

	i = 0;
	while (i < child_count)
	{
		if (waitpid(-1, &status, 0) == -1)
			break ;
		if (WIFEXITED(status))
			shell->exitcode = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exitcode = 128 + WTERMSIG(status);
		
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
		exit(exec_builtin(shell, cmd));
	else
		exit(exec_external(shell, cmd));
	exit(1);
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
	t_cmd	*cur;
	int		pipefd[2];
	int		in_fd;
	pid_t	pid;
	int		child_count;

	cur = cmd;
	child_count = 0;
	in_fd = STDIN_FILENO;
	while (cur)
	{
		if (cur->next && pipe(pipefd) == -1)
			return (cmd_err(shell, "pipe", strerror(errno), 1));
		pid = fork();
		if (pid == -1)
			return (cmd_err(shell, "fork", strerror(errno), 1));
		if (pid == 0)
			child(shell, cur, in_fd, pipefd);
		in_fd = parent(in_fd, pipefd, cur);
		child_count++;
		cur = cur->next;
	}
	return (wait_all_children(shell, child_count));
}
