/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:36:09 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/13 18:39:58 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

	key = NULL;
	value = NULL;

	equal_sign = ft_strchr(env_str, '=');
	if (equal_sign)
	{
		key = malloc(equal_sign - env_str + 1);
		value = ft_strdup(equal_sign + 1);
		ft_strlcpy(key, env_str, equal_sign - env_str + 1);
		key[equal_sign - env_str] = '\0';
		add_env(env_list, key, value, true);
		free(key);
		free(value);
	}
	else
		add_env(env_list, key, value, true);
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

	while (env_list)
	{
		tmp = env_list->next;
		free(env_list->key);
		if (env_list->value)
			free(env_list->value);
		free(env_list);
		env_list = tmp;
	}
}
