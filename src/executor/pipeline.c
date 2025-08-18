/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:55:37 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/18 16:16:32 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	setup_child_io(t_cmd *cmd, int in_fd, int pipefd[2],
						bool skip_stdin)
{
	if (!skip_stdin && in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	else if (skip_stdin && in_fd != STDIN_FILENO)
		close(in_fd);
	if (cmd->next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
}

static void	child(t_shell *shell, t_cmd *cmd, int in_fd, int pipefd[2])
{
	bool		has_input_redir;
	t_redirect	*last_in;

	sig_dfl();
	last_in = get_last_input_redir(cmd->redirects);
	has_input_redir = (last_in && (last_in->type == REDIR_IN
				|| (last_in->type == REDIR_HEREDOC && last_in->hdoc_fd >= 0)));
	setup_child_io(cmd, in_fd, pipefd, has_input_redir);
	if (!cmd->argv)
	{
		if (setup_redir(shell, cmd))
		{
			cleanup(shell);
			exit(shell->exitcode);
		}
		cleanup(shell);
		exit(0);
	}
	shell->exitcode = exec_cmd(shell, cmd);
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
	pid_t	pids[30848];

	signal(SIGINT, SIG_IGN);
	child_count = 0;
	in_fd = STDIN_FILENO;
	while (cmd)
	{
		pid = create_process(shell, cmd, pipefd);
		if (pid == -1)
			return (shell->exitcode);
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
