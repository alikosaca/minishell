/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:51:28 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/14 00:06:23 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

void	c_heredoc(t_shell *shell, t_redirect *redir, int fd[2])
{
	char	*line;

	line = NULL;
	signal(SIGINT, SIG_DFL);
	close(fd[0]);
	while (true)
	{
		line = readline(PS2);
		if (!line)
			break ;
		if (is_it_over(redir, line))
			break ;
		if (g_sig == 130)
		{
			shell->exitcode = g_sig;
			g_sig = 0;
			break ;
		}
		should_be_expand(shell, redir, &line);
		print_line(fd, line);
	}
	cleanup(shell);
	close(fd[1]);
	exit(0);
}

int	p_heredoc(t_shell *shell, pid_t pid, int fd[2], bool should_dup)
{
	int	status;

	close(fd[1]);
	waitpid(pid, &status, 0);
	interactive_signals();
	if (g_sig == 130)
	{
		shell->exitcode = g_sig;
		g_sig = 0;
		close(fd[0]);
		return (shell->exitcode);
	}
	return (restore_doc_fds(shell, fd, should_dup));
}
