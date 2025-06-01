/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:24:44 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/01 15:25:41 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	count_exported_env(t_env *env_list)
{
	int		count;
	t_env	*curr;

	count = 0;
	curr = env_list;
	while (curr)
	{
		if (curr->exported && curr->value)
			count++;
		curr = curr->next;
	}
	return (count);
}

char	*create_env_string(char *key, char *value)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, value);
	free(tmp);
	return (result);
}

char	**env_to_arr(t_env *env_list)
{
	char	**env_arr;
	int		count;
	int		i;
	t_env	*curr;

	count = count_exported_env(env_list);
	env_arr = ft_calloc(count + 1, sizeof(char *));
	if (!env_arr)
		return (NULL);
	i = -1;
	curr = env_list;
	while (curr && ++i < count)
	{
		if (curr->exported && curr->value)
		{
			env_arr[i] = create_env_string(curr->key, curr->value);
			if (!env_arr[i])
			{
				free_env_arr(env_arr);
				return (NULL);
			}
		}
		curr = curr->next;
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
