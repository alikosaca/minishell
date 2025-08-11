/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:55:37 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/11 15:34:58 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

static void	setup_child_io(t_cmd *cmd, int in_fd, int pipefd[2])
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
}

static int	execute_cmd(t_shell *shell, t_cmd *cmd)
{
	if (cmd->argv)
	{
		if (is_builtin(cmd))
			return (exec_builtin(shell, cmd));
		else
			return (exec_external(shell, cmd));
	}
	return (0);
}

static void	child(t_shell *shell, t_cmd *cmd, int in_fd, int pipefd[2])
{
	signal(SIGINT, SIG_DFL);
	setup_child_io(cmd, in_fd, pipefd);
	if (setup_redir(shell, cmd))
	{
		cleanup(shell);
		exit(shell->exitcode);
	}
	shell->exitcode = execute_cmd(shell, cmd);
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
