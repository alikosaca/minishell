/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:36:09 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/18 03:05:44 by yaycicek         ###   ########.fr       */
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

void	add_sys_env(t_env **envlist, char *envstr)
{
	char	*key;
	char	*equal;
	char	*value;

	key = NULL;
	equal = NULL;
	value = NULL;

	equal = ft_strchr(envstr, '=');
	if (equal)
	{
		key = malloc(equal - envstr + 1);
		value = ft_strdup(equal + 1);
		ft_strlcpy(key, envstr, equal - envstr + 1);
		key[equal - envstr] = '\0';
		add_env(envlist, key, value, true);
		free(key);
		free(value);
	}
	else
	{
		key = envstr;
		add_env(envlist, key, value, true);
	}
}

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*envlist;

	envlist = NULL;
	i = 0;
	while (envp[i])
	{
		add_sys_env(&envlist, envp[i]);
		i++;
	}
	return (envlist);
}

void	free_envlist(t_env *envlist)
{
	t_env	*tmp;

	while (envlist)
	{
		tmp = envlist->next;
		free(envlist->key);
		if (envlist->value)
			free(envlist->value);
		free(envlist);
		envlist = tmp;
	}
}
