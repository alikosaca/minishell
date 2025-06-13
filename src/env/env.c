/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:30:39 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/13 19:24:35 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env(t_env *env_list)
{
	while (env_list)
	{
		if (env_list->value && env_list->exported)
			printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
}
