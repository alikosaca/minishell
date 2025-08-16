/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:30:39 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/16 21:03:50 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	env(t_env *envlist, char **argv)
{
	if (argv[1])
		return (0);
	while (envlist)
	{
		if (envlist->value && envlist->exported)
			printf("%s=%s\n", envlist->key, envlist->value);
		envlist = envlist->next;
	}
	return (0);
}
