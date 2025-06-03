/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:30:39 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/03 14:20:08 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"
#include <stdio.h>

void	env(t_env *env_list)
{
	while (env_list)
	{
		if (env_list->exported && env_list->value)
			printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
}
