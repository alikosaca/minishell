/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:42:55 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/24 21:13:10 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/executor.h"

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

int redir_heredoc(t_shell *shell, t_redirect *redir, bool should_dup)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (cmd_err(shell, "pipe", strerror(errno), 1));
	while (true)
	{
		line = readline(PS2);
		if (shell->exitcode == 130)
			break ;
		if (!line)
			break ;
		if (is_it_over(redir, fd, line))
			break ;
		should_be_expand(redir, line);
		print_line(fd, line);
	}
	return (restore_doc_fds(shell, fd, should_dup));
}

int setup_redir(t_shell *shell, t_cmd *cmd)
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
		redir = redir->next;
	}
	return (shell->exitcode);
}
