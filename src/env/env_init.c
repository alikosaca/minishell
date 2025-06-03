/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:36:09 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/03 16:41:58 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"

t_env	*create_env_node(char *key, char *value, bool exported)
{
	t_env	*node;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free(node);
		return (NULL);
	}
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
		{
			free(node);
			free(node->key);
			return (NULL);
		}
	}
	node->exported = exported;
	node->next = NULL;
	return (node);
}

void	add_sys_env(t_env **env_list, char *env_str)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	equal_sign = ft_strchr(env_str, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		key = env_str;
		value = equal_sign + 1;
		add_env(env_list, key, value, true);
	}
}

t_env	*init_env(char **envp)
{
	t_env	*env_list;
	int		i;

	env_list = NULL;
	i = -1;
	while (envp[++i])
		add_sys_env(&env_list, envp[i]);
	return (env_list);
}

void	free_env_list(t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		env_list = env_list->next;
		free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}
