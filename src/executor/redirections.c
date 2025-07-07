/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:42:55 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/07 21:58:03 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/executor.h"

static int	redir_in(t_shell *shell, t_redirect *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
		return (cmd_err(shell, "infile", strerror(errno), 1)); // !!
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	redir_out(t_shell *shell, t_redirect *redir)
{
	int	fd;

	fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (cmd_err(shell, "outfile", strerror(errno), 1));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	redir_append(t_shell *shell, t_redirect *redir)
{
	int	fd;

	fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (cmd_err(shell, "outfile", strerror(errno), 1));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	redir_heredoc(t_shell *shell, t_redirect *redir)
{
	(void)shell;
	(void)redir;
	return (shell->exitcode);
}

int	setup_redir(t_shell *shell, t_cmd *cmd)
{
	t_redirect	*redir;

	if (!cmd || !cmd->redirects)
		return (0);
	redir = cmd->redirects;
	while (redir)
	{
		printf("redir->type: %d\n", redir->type);
		if (redir->type == REDIR_IN)
		 	shell->exitcode = redir_in(shell, redir);
		else if (redir->type == REDIR_OUT)
		{
			printf("3\n");
			shell->exitcode = redir_out(shell, redir);
		}
		else if (redir->type == REDIR_APPEND)
		 	shell->exitcode = redir_append(shell, redir);
		else if (redir->type == REDIR_HEREDOC)
		 	shell->exitcode = redir_heredoc(shell, redir);
		redir = redir->next;
	}
	return (shell->exitcode);
}
