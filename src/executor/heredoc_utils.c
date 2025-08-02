/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:26:24 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/02 17:47:53 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

int	is_it_over(t_redirect *redir, char *line)
{
	if (!line || !redir || !redir->delimiter)
		return (0);
	if (ft_strcmp(line, redir->delimiter) == 0)
	{
		_free(&line);
		return (1);
	}
	return (0);
}

void	print_line(int fd[2], char *line)
{
	write(fd[1], line, ft_strlen(line));
	write(fd[1], "\n", 1);
	_free(&line);
}

void	should_be_expand(t_shell *shell, t_redirect *redir, char **line)
{
	char	*temp;
	int		i;

	i = 0;
	if (redir->should_be_expand)
	{
		temp = expand_dollar(shell, *line, &i);
		_free(line);
		*line = temp;
	}
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
