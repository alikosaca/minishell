/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 00:16:20 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/01 19:12:02 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/expansion.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char *result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

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

char	*expand_dollar(t_shell *shell, char *str)
{

	char	*fp;
	int		i;
	int		start;
	char	*var_name;

	if (!shell || !str)
		return (NULL);
	fp = find_process(str, &i);
	if (!str[i])
		return (fp);
	if (str[i] == '?')
		return (ft_itoa(shell->exitcode));
	start = i;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = ft_substr(str, start, i - start);
	if (start % 2 != 0)
		var_name = get_env_value(shell->envlist, var_name);
	if (!var_name)
		var_name = ft_strdup("");
	fp = ft_strjoin_free(fp, var_name);
	free(var_name);
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
	free(ret);
	free(part);

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