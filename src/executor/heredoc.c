/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:51:28 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/15 02:30:39 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

void	c_heredoc(t_shell *shell, t_redirect *redir, int fd[2])
{
	char	*line;

	line = NULL;
	close(fd[0]);
	heredoc_signals();
	while (true)
	{
		line = readline(PS2);
		if (!line)
		{
			if (g_sig == 130)
				shell->exitcode = 130;
			break ;
		}
		if (is_it_over(redir, line))
			break ;
		should_be_expand(shell, redir, &line);
		print_line(fd, line);
	}
	cleanup(shell);
	close(fd[1]);
	exit(shell->exitcode);
}

int	p_heredoc(t_shell *shell, pid_t pid, int fd[2])
{
	int	status;

	close(fd[1]);
	if (waitpid(pid, &status, 0) == -1)
	{
		close(fd[0]);
		cmd_err(shell, "waitpid", strerror(errno), 1);
		return (-1);
	}
	interactive_signals();
	shell->exitcode = WEXITSTATUS(status);
	if (shell->exitcode == 130)
	{
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}
