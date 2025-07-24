/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:26:24 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/24 21:14:29 by yaycicek         ###   ########.fr       */
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

void	print_line(int fd[2], char *line)
{
	write(fd[1], line, ft_strlen(line));
	write(fd[1], "\n", 1);
	free(line);
}

void	should_be_expand(t_redirect *redir, char *line)
{
	if (redir->should_be_expand)
		ft_strdup(line); // for now.
	else
		ft_strdup(line); // for now.
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
