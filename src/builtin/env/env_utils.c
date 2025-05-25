/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:01:16 by yaycicek          #+#    #+#             */
/*   Updated: 2025/05/25 16:14:44 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
** env_list'e yeni bir node ekleyen/node'u güncelleyen fonksiyon
*/
t_env	*add_env(t_env **env_list, char *key, char *value, bool *exported)
{
	t_env	*node;

	if (!key)
		return (NULL);
	node = find_env(*env_list, key);
	if (node)
	{
		if (value)
		{
			free(node->value);
			node->value = ft_strdup(value);
		}
		if (exported)
			node->exported = true;
		return (node);
	}
	node = create_env_node(key, value, exported);
	if (!node)
		return (NULL);
	node->next = *env_list;
	*env_list = node;
	return (node);
}

/*
** env_list'ten env_node silen fonksiyon
*/
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
