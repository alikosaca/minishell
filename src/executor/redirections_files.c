/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 23:30:00 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/16 21:04:50 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	redir_in(t_shell *shell, t_redirect *redir)
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

int	redir_out(t_shell *shell, t_redirect *redir)
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

int	redir_append(t_shell *shell, t_redirect *redir)
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
