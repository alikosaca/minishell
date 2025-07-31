/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 00:16:20 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/31 21:18:34 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/expansion.h"

static char *find_process(char *str, int *i)
{
	int		status;
	char	*res;
	char	*tmp;

	res = ft_strdup("");
	status = 0;
	while (str[(*i)] == '$')
	{
		status++;
		(*i)++;
		if (status == 2)
		{
			tmp = ft_strjoin(res, "42");
			free(res);
			res = tmp;
			status = 0;
		}
	}
	if (status == 1)
	{
		tmp = ft_strjoin(res, "$");
		free(res);
		res = tmp;
	}
	return (res);
}

char	*expand_dollar(t_shell *shell, char *str)
{
	char	*value;
	char	*fp;
	//char	*tmp;
	int		i;
	int		start;
	char *var_name;
	char *env_val;

	if (!shell || !str)
		return (NULL);
	i = 0;
	fp = find_process(str, &i);
	if (!str[i])
		return (fp);
	if (str[i] == '?')
	{
		value = ft_itoa(shell->exitcode);
		i++;
	}
	else
	{
		start = i;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		var_name = ft_substr(str, start, i - start);
		env_val = get_env_value(shell->envlist, var_name);
		value = ft_strdup(env_val ? env_val : "");
		free(var_name);
	}
	fp = ft_strjoin(fp, value);
	//free(fp);
	free(value);
	return (fp);
}

// static int	var_len(char *str)
// {
	// 	int	i;
	
	// 	if (!str)
	// 		return (0);
	// 	if (*str == '?')
	// 		return (1);
	// 	i = 0;
	// 	while (str[i])
	// 		i++;
	// 	return (i);
	// }
	
	// ft_strdup();
	
	// static int	var_len(char *str)
	// {
// 	int	i;

// 	if (!str)
// 		return (0);
// 	if (*str == '?')
// 		return (1);
// 	i = 0;
// 	while (str[i] )
// 		i++;
// 	return (i);
// }

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

static char	*get_var_value(t_shell *shell, char *str, int *i)
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

