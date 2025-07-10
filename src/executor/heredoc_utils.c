/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:26:24 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/09 19:46:56 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

int	heredoc1(t_shell *shell, int fd[2], char *line)
{
	if (g_exit_status == 130)
	{
		printf("heredoc1(1), g_exit_status: %d\n", g_exit_status);
		printf("heredoc1(1), shell->exitcode: %d\n", shell->exitcode);
		shell->exitcode = g_exit_status;
		g_exit_status = 0;
		printf("heredoc1(2), g_exit_status: %d\n", g_exit_status);
		printf("heredoc1(2), shell->exitcode: %d\n", shell->exitcode);
		if (line)
			free(line);
		close(fd[0]);
		close(fd[1]);
		return (shell->exitcode);
	}
	if (!line)
	{
		close(fd[1]);
		return (shell->exitcode);
	}
	return (0);
}

int	is_it_over(t_redirect *redir, int fd[2], char *line)
{
	if (!line)
		return (0);
	if (ft_strcmp(line, redir->delimiter) == 0)
	{
		free(line);
		close(fd[1]);
		return (0);
	}
	return (1);
}

void	print_line(int fd[2], char *line, char *expanded_line)
{
	write(fd[1], expanded_line, ft_strlen(expanded_line));
	write(fd[1], "\n", 1);
	free(line);
	if (expanded_line != line)
		free(expanded_line);
}

char	*should_be_expand(t_redirect *redir, char *line)
{
	char	*expanded;

	expanded = NULL;
	if (redir->should_be_expand)
		expanded = ft_strdup(line); // for now.
	else
		expanded = ft_strdup(line);	// for now.
	return (expanded);
}

t_redirect	*get_last_redir(t_redirect *redir)
{
	t_redirect	*last;
	
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
			last = redir;
		redir = redir->next;
	}
	return (last);
}
