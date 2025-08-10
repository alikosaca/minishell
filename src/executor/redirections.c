/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:42:55 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/10 13:25:52 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

static int	redir_in(t_shell *shell, t_redirect *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
		return (cmd_err(shell, redir->file, strerror(errno), 1));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (cmd_err(shell, "dup2", strerror(errno), 1));
	close(fd);
	return (0);
}

static int	redir_out(t_shell *shell, t_redirect *redir)
{
	int	fd;

	fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (cmd_err(shell, redir->file, strerror(errno), 1));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (cmd_err(shell, "dup2", strerror(errno), 1));
	close(fd);
	return (0);
}

static int	redir_append(t_shell *shell, t_redirect *redir)
{
	int	fd;

	fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (cmd_err(shell, redir->file, strerror(errno), 1));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (cmd_err(shell, "dup2", strerror(errno), 1));
	close(fd);
	return (0);
}

static int	redir_heredoc(t_shell *shell, t_redirect *redir, bool should_dup)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (cmd_err(shell, "pipe", strerror(errno), 1));
	heredoc_signals();
	pid = fork();
	if (pid == -1)
		return (cmd_err(shell, "fork", strerror(errno), 1));
	if (pid == 0)
		c_heredoc(shell, redir, fd);
	return (p_heredoc(shell, pid, fd, should_dup));
}

int	setup_redir(t_shell *shell, t_cmd *cmd)
{
	t_redirect	*redir;
	t_redirect	*last;

	if (!cmd || !cmd->redirects)
		return (0);
	redir = cmd->redirects;
	last = get_last_redir(redir);
	while (redir)
	{
		if (redir->type == REDIR_IN)
			shell->exitcode = redir_in(shell, redir);
		else if (redir->type == REDIR_OUT)
			shell->exitcode = redir_out(shell, redir);
		else if (redir->type == REDIR_APPEND)
			shell->exitcode = redir_append(shell, redir);
		else if (redir->type == REDIR_HEREDOC)
			shell->exitcode = redir_heredoc(shell, redir, redir == last);
		if (shell->exitcode == 130)
			return (shell->exitcode);
		redir = redir->next;
	}
	return (shell->exitcode);
}
