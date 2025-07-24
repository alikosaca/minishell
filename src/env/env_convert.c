/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:24:44 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/24 13:04:58 by yaycicek         ###   ########.fr       */
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
	free(tmp);
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
				free_env_arr(env_arr);
				return (NULL);
			}
		}
		tmp = tmp->next;
	}
	return (env_arr);
}

void	free_env_arr(char **env_arr)
{
	int	i;

	if (!env_arr)
		return ;
	i = 0;
	while (env_arr[i])
	{
		free(env_arr[i]);
		i++;
	}
	free(env_arr);
}
