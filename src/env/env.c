/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:30:39 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/18 03:05:54 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/env.h"

void	env(t_env *envlist)
{
	while (envlist)
	{
		if (envlist->value && envlist->exported)
			printf("%s=%s\n", envlist->key, envlist->value);
		envlist = envlist->next;
	}
}
