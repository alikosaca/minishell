/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 00:16:20 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/18 21:23:45 by akosaca          ###   ########.fr       */
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
		return (ft_itoa(shell->exitcode));
	value = get_env_value(shell->envlist, str);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
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

