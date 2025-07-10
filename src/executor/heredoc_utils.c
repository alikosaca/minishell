/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:26:24 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/10 23:57:22 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

int	is_it_over(t_redirect *redir, int fd[2], char *line)
{
	if (!line)
		return (0);
	if (ft_strcmp(line, redir->delimiter) == 0)
	{
		free(line);
		close(fd[1]);
		return (1);
	}
	return (0);
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
