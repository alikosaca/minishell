/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 00:16:20 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/02 13:59:50 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expansion.h"

static char	*find_process(char *str, int *i)
{
	char	*res;
	int		status;

	(*i) = 0;
	res = ft_strdup("");
	status = 0;
	while (str[(*i)] == '$')
	{
		status++;
		(*i)++;
		if (status == 2)
		{
			res = ft_strjoin_free(res, "42");
			status = 0;
		}
	}
	if (status == 1 && !str[(*i)])
		res = ft_strjoin_free(res, "$");
	return (res);
}

static char	*env_value_handle(t_shell *shell, char *var_value, int start)
{
	char	*env_value;

	if (start % 2 != 0 || start == 0)
	{
		env_value = get_env_value(shell->envlist, var_value);
		if (!env_value)
			return (ft_strdup(""));
		else
			return (ft_strdup(env_value));
	}
	else
		return (ft_strdup(""));
}

char	*expand_dollar(t_shell *shell, char *str)
{
	char	*fp;
	int		i;
	int		start;
	char	*var_value;
	char	*env_value;

	if (!shell || !str)
		return (NULL);
	fp = find_process(str, &i);
	if (!str[i])
		return (fp);
	if (str[i] == '?')
	{
		_free(&fp);
		return (ft_itoa(shell->exitcode));
	}
	start = i;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_value = ft_substr(str, start, i - start);
 	env_value = env_value_handle(shell, var_value, start);
	_free(&var_value);
	fp = ft_strjoin_free(fp, env_value);
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

static char	*add_dquote(char *ret, char *part)
{
	char	*tmp;

	tmp = ft_strjoin(ret, part);
	_free(&ret);
	_free(&part);

	return (tmp);
}
char	*expand_dquote(t_shell *shell, char *str)
{
	int		i;
	int		start;
	char	*ret;
	char	*part;

	i = 0;
	ret = ft_strdup("");
	while (str[i] && str[i] != '"')
	{
		if (str[i] == '$')
		{
			i++;
			part = get_var_value(shell, str, &i);
		}
		else
		{
			start = i;
			while (str[i] && str[i] != '$')
				i++;
			part = ft_substr(str, start, i - start);
		}
		ret = add_dquote(ret, part);
	}
	return (ret);
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
