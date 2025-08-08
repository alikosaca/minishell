/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:26:24 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/08 20:26:27 by yaycicek         ###   ########.fr       */
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
	int		start;
	char	*res;

	i = 0;
	temp = NULL;
	if (redir->should_be_expand)
	{
		res = ft_strdup("");
		while ((*line)[i])
		{
			if ((*line)[i] == '$')
			{
				if ((*line)[i + 1] && (ft_isalnum((*line)[i + 1]) || \
					(*line)[i + 1] == '_' || (*line)[i + 1] == '?' || (*line)[i + 1] == '$'))
					temp = expand_dollar(shell, (*line), &i);
				else
				{
					temp = ft_strdup("$");
					i++;
				}
			}
			else
			{
				start = i;
				while ((*line)[i] && (*line)[i] != '$')
					i++;
				temp = ft_substr((*line), start, i - start);
			}
			res = ft_strjoin_free_first(res, temp);
		}
		_free(line);
		*line = res;
	}
}

t_redirect	*get_last_redir(t_redirect *redir)
{
	t_redirect	*last;

	last = NULL;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
			last = redir;
		redir = redir->next;
	}
	return (last);
}
