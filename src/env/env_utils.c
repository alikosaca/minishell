/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:01:16 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/10 13:27:06 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"

static void	add_env_to_end(t_env **envlist, t_env *node)
{
	t_env	*tmp;

	if (!(*envlist))
		(*envlist) = node;
	else
	{
		tmp = (*envlist);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

t_env	*add_env(t_env **envlist, char *key, char *value, bool exported)
{
	t_env	*node;

	if (!key)
		return (NULL);
	node = find_env(*envlist, key);
	if (node)
	{
		if (value)
		{
			if (node->value)
				_free((void **)&node->value);
			node->value = ft_strdup(value);
		}
		node->exported = exported;
		return (node);
	}
	node = create_env_node(key, value, exported);
	if (!node)
		return (NULL);
	add_env_to_end(envlist, node);
	return (node);
}

void	remove_env(t_env **envlist, char *key)
{
	t_env	*prev;
	t_env	*cur;

	if (!envlist || !*envlist || !key)
		return ;
	prev = NULL;
	cur = *envlist;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				(*envlist) = cur->next;
			_free((void **)&cur->key);
			_free((void **)&cur->value);
			_free((void **)&cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

t_env	*find_env(t_env *envlist, char *key)
{
	if (!key)
		return (NULL);
	while (envlist)
	{
		if (ft_strcmp(envlist->key, key) == 0)
			return (envlist);
		envlist = envlist->next;
	}
	return (NULL);
}

char	*get_env_value(t_env *env_list, char *key)
{
	t_env	*node;

	node = find_env(env_list, key);
	if (!node)
		return (NULL);
	return (node->value);
}
