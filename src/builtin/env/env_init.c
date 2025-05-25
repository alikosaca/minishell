/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:36:09 by yaycicek          #+#    #+#             */
/*   Updated: 2025/05/25 15:13:15 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"

/*
** Yeni bir env_node oluşturan fonksiyon
*/
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

/*
** Sistemin kendi env'sinden kendi env yapımızı oluşturmayı sağlayan fonksiyon
*/
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
