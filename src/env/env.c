/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:36:09 by yaycicek          #+#    #+#             */
/*   Updated: 2025/05/25 14:47:02 by yaycicek         ###   ########.fr       */
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
