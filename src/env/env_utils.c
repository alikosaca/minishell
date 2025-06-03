/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:01:16 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/03 14:16:38 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"

void	add_env_to_end(t_env **env_list, t_env *node)
{
	t_env	*tmp;

	if (!*env_list)
		*env_list = node;
	else
	{
		tmp = *env_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

t_env	*add_env(t_env **env_list, char *key, char *value, bool exported)
{
	t_env	*node;

	if (!key)
		return (NULL);
	node = find_env(*env_list, key);
	if (node)
	{
		if (value)
		{
			if (node->value)
				free(node->value);
			node->value = ft_strdup(value);
		}
		node->exported = exported;
		return (node);
	}
	node = create_env_node(key, value, exported);
	if (!node)
		return (NULL);
	add_env_to_end(env_list, node);
	return (node);
}

void	remove_env(t_env **env_list, char *key)
{
	t_env	*curr;
	t_env	*prev;

	if (!env_list || !*env_list || !key)
		return ;
	curr = *env_list;
	prev = NULL;
	while (curr)
	{
		if (ft_strlen(curr->key) == ft_strlen(key) &&
			ft_strncmp(curr->key, key, ft_strlen(key)) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env_list = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

t_env	*find_env(t_env *env_list, char *key)
{
	size_t	key_len;

	if (!key)
		return (NULL);
	key_len = ft_strlen(key);
	while (env_list)
	{
		if (ft_strlen(env_list->key) == key_len &&
			ft_strncmp(env_list->key, key, key_len) == 0)
			return (env_list);
		env_list = env_list->next;
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
