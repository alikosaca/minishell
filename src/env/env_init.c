/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:36:09 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/09 18:40:17 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"

t_env	*create_env_node(char *key, char *value, bool exported)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
	{
		_free((void **)&node);
		return (NULL);
	}
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
		{
			_free((void **)&node->key);
			_free((void **)&node);
			return (NULL);
		}
	}
	node->exported = exported;
	node->next = NULL;
	return (node);
}

void	*add_sys_env(t_env **envlist, char *envstr)
{
	char	*key;
	char	*equal;
	char	*value;

	key = NULL;
	value = NULL;
	equal = ft_strchr(envstr, '=');
	if (equal)
	{
		key = ft_substr(envstr, 0, equal - envstr);
		value = ft_strdup(equal + 1);
		if (!add_env(envlist, key, value, true))
			return (NULL);
		_free((void **)&key);
		_free((void **)&value);
	}
	else
	{
		key = envstr;
		if (!add_env(envlist, key, value, true))
			return (NULL);
	}
	return ((void *)1);
}

void	*init_envlist(t_env **envlist, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!add_sys_env(envlist, envp[i]))
			return (NULL);
		i++;
	}
	return ((void *)1);
}

void	free_envlist(t_env **envlist)
{
	t_env	*tmp;

	while ((*envlist))
	{
		tmp = (*envlist)->next;
		_free((void **)&(*envlist)->key);
		if ((*envlist)->value)
			_free((void **)&(*envlist)->value);
		free((*envlist));
		(*envlist) = tmp;
	}
}
