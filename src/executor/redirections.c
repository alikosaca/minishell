/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:42:55 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/31 12:43:48 by yaycicek         ###   ########.fr       */
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

void	child_heredoc(t_shell *shell, t_redirect *redir, int *fd)
{
	char	*line;

	line = NULL;
	signal(SIGINT, SIG_DFL);
	close(fd[0]);
	while (1)
	{
		line = readline(PS2);
		if (!line)
			break ;
		if (is_it_over(redir, line))
			break ;
		if (g_sig == 130)
		{
			shell->heredoc = false;
			shell->exitcode = g_sig;
			g_sig = 0;
			break ;
		}
		should_be_expand(shell, redir, &line);
		print_line(fd, line);
	}
	close(fd[1]);
	exit(0);
}

int	redir_heredoc(t_shell *shell, t_redirect *redir, bool should_dup)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (!redir || pipe(fd) == -1)
		return (cmd_err(shell, "pipe", strerror(errno), 1));
	shell->heredoc = true;
	pid = fork();
	if (pid == -1)
		return (cmd_err(shell, "fork", strerror(errno), 1));
	if (pid == 0)
		child_heredoc(shell, redir, fd);
	close(fd[1]);
	waitpid(pid, &status, 0);
	shell->heredoc = false;
	if (g_sig == 130) // || (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		shell->exitcode = g_sig;
		g_sig = 0;
		close(fd[0]);
		return (shell->exitcode);
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
		if (shell->exitcode == 130)
			return (shell->exitcode);
		redir = redir->next;
	}
	return (shell->exitcode);
}
