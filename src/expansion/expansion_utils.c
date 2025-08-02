/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 00:16:20 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/02 20:13:53 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expansion.h"

static char	*find_process(char *str, int *i, int *count)
{
	char	*res;
	int		status;
	int		pos;

	(*count) = 0;
	res = ft_strdup("");
	status = 0;
	pos = (*i);
	while (str[pos] == '$')
	{
		status++;
		pos++;
		(*count)++;
		if (status == 2)
		{
			res = ft_strjoin_free_first(res, "42");
			status = 0;
		}
	}
	if (status == 1 && !str[pos])
		res = ft_strjoin_free_first(res, "$");
	(*i) += (*count);
	return (res);
}

static char	*env_value_handle(t_shell *shell, char *var_value, int *count)
{
	char	*env_value;

	if ((*count) % 2 != 0 || (*count) == 0)
	{
		env_value = get_env_value(shell->envlist, var_value);
		if (!env_value)
			return (ft_strdup(""));
		else
			return (ft_strdup(env_value));
	}
	else
		return (ft_strdup(var_value));
}

char	*expand_dollar(t_shell *shell, char *str, int *i)
{
	char	*fp;
	int		start;
	char	*var_value;
	char	*env_value;
	int		count;

	if (!shell || !str)
		return (NULL);
	fp = find_process(str, i, &count);
	if (!str[*i])
		return (fp);
	if (str[*i] == '?')
	{
		_free(&fp);
		(*i)++;
		return (ft_itoa(shell->exitcode));
	}
	start = (*i);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_value = ft_substr(str, start, (*i) - start);
 	env_value = env_value_handle(shell, var_value, &count);
	_free(&var_value);
	fp = ft_strjoin_free_first(fp, env_value);
	_free(&env_value);
	return (fp);
}

static int	env_len(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (*str == '?')
		return (1);
	i = 0;
	while (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

static char	*ft_strjoin_free_both(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	_free(&s1);
	_free(&s2);

	return (result);
}
/*
	if (str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
		part = expand_dollar(shell, str, &i);
	else
	{
		part = ft_strdup("$");
		i++;
	}
*/
char	*expand_dquote(t_shell *shell, char *str)
{
	int		i;
	int		start;
	char	*res;
	char	*part;

	i = 0;
	res = ft_strdup("");
	while (str[i] && str[i] != '"')
	{
		if (str[i] == '$')
		{
			part = expand_dollar(shell, str, &i);
		}
		else
		{
			start = i;
			while (str[i] && str[i] != '$' && str[i] != '"')
				i++;
			part = ft_substr(str, start, i - start);
		}
		res = ft_strjoin_free_both(res, part);
	}
	return (res);
}

char	*get_var_value(t_shell *shell, char *str, int *i)
{
	char	*env;
	char	*val;

	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->exitcode));
	}
	env = ft_substr(str, *i, env_len(&str[*i]));
	*i += ft_strlen(env);
	val = get_env_value(shell->envlist, env);
	if (!val)
		val = ft_strdup("");
	else
		val = ft_strdup(val);
	free(env);

	return (val);
}
