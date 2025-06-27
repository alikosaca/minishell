/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 00:16:20 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/28 00:18:49 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/expansion.h"

char	*expand_dollar(t_shell *shell, char *str)
{
	char	*value;

	if (!shell || !str)
		return (NULL);
	str++;
	if (ft_strncmp(str, "?", 1) == 0)
		return (ft_itoa(shell->last_exit_code));
	value = get_env_value(shell->envlist, str);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static int	var_len(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (*str == '?')
		return (1);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*get_var_value(t_shell *shell, char *str, int *i)
{
	char	*key;
	char	*val;

	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->last_exit_code));
	}
	key = ft_substr(str, *i, var_len(&str[*i]));
	*i += ft_strlen(key);
	val = get_env_value(shell->envlist, key);
	if (!val)
		val = ft_strdup("");
	else
		val = ft_strdup(val);
	free(key);
	return (val);
}

char	*expand_dquote(t_shell *shell, char *str)
{
	int		i;
	int		start;
	char	*ret;
	char	*tmp;
	char	*part;

	i = 0;
	ret = ft_strdup("");
	while (str[i])
	{
		if (str[i++] == '$')
			part = get_var_value(shell, str, &i);
		else
		{
			start = i;
			while (str[i] && str[i] != '$')
				i++;
			part = ft_substr(str, start, i - start);
		}
		tmp = ft_strjoin(ret, part);
		free(ret);
		free(part);
		ret = tmp;
	}
	return (ret);
}
