/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:24:44 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/01 14:43:28 by yaycicek         ###   ########.fr       */
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
