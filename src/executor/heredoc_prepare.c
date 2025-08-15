/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prepare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:15:00 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/15 02:31:08 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

static int	fork_heredoc_child(t_shell *shell, t_redirect *redir, int fd[2])
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		cmd_err(shell, "fork", strerror(errno), 254);
		return (-1);
	}
	if (pid == 0)
		c_heredoc(shell, redir, fd);
	return (p_heredoc(shell, pid, fd));
}

static int	prepare_single_heredoc(t_shell *shell, t_redirect *redir)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		cmd_err(shell, "pipe", strerror(errno), 1);
		return (-1);
	}
	return (fork_heredoc_child(shell, redir, fd));
}

int	prepare_heredocs_for_cmd(t_shell *shell, t_redirect *redir)
{
	t_redirect	*rd;

	rd = redir;
	while (rd && shell->exitcode == 0)
	{
		if (rd->type == REDIR_HEREDOC)
		{
			if (rd->hdoc_fd >= 0)
			{
				close(rd->hdoc_fd);
				rd->hdoc_fd = -1;
			}
			rd->hdoc_fd = prepare_single_heredoc(shell, rd);
			if (rd->hdoc_fd < 0)
			{
				if (shell->exitcode != 0)
					return (shell->exitcode);
				else
					return (1);
			}
		}
		rd = rd->next;
	}
	return (0);
}
