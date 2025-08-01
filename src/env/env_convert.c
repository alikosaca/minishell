/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:24:44 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/02 00:41:48 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"

int	count_exported_env(t_env *envlist)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = envlist;
	while (tmp)
	{
		if (tmp->exported && tmp->value)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

char	*create_envstr(char *key, char *value)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	ret = ft_strjoin(tmp, value);
	_free(&tmp);
	return (ret);
}

char	**env_to_arr(t_env *envlist)
{
	int		i;
	int		count;
	char	**env_arr;
	t_env	*tmp;

	count = count_exported_env(envlist);
	env_arr = malloc(sizeof(char *) * (count + 1));
	if (!env_arr)
		return (NULL);
	i = -1;
	tmp = envlist;
	while (tmp && ++i < count)
	{
		if (tmp->exported && tmp->value)
		{
			env_arr[i] = create_envstr(tmp->key, tmp->value);
			if (!env_arr[i])
			{
				__free(&env_arr);
				return (NULL);
			}
		}
		tmp = tmp->next;
	}
	return (env_arr);
}
