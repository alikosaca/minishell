/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:26:24 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/09 18:29:53 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

int	is_it_over(t_redirect *redir, char *line)
{
	if (!line || !redir || !redir->delimiter)
		return (0);
	if (ft_strcmp(line, redir->delimiter) == 0)
	{
		_free((void **)&line);
		return (1);
	}
	return (0);
}

static char	*handle_dollar(t_shell *shell, char *line, int *i)
{
	char	*temp;

	if (line[*i + 1] && (ft_isalnum(line[*i + 1]) || line[*i + 1] == '_' || \
		line[*i + 1] == '?' || line[*i + 1] == '$'))
		temp = expand_dollar(shell, line, i);
	else
	{
		temp = ft_strdup("$");
		(*i)++;
	}
	return (temp);
}

static char	*handle_non_dollar(char *line, int *i)
{
	int		start;
	char	*temp;

	start = *i;
	while (line[*i] && line[*i] != '$')
		(*i)++;
	temp = ft_substr(line, start, *i - start);
	return (temp);
}

void	should_be_expand(t_shell *shell, t_redirect *redir, char **line)
{
	char	*res;
	char	*temp;
	int		i;

	if (!redir->should_be_expand)
		return ;
	res = ft_strdup("");
	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
			temp = handle_dollar(shell, *line, &i);
		else
			temp = handle_non_dollar(*line, &i);
		res = ft_strjoin_free_first(res, temp);
	}
	_free((void **)line);
	*line = res;
}

void	print_line(int fd[2], char *line)
{
	write(fd[1], line, ft_strlen(line));
	write(fd[1], "\n", 1);
	_free((void **)&line);
}
