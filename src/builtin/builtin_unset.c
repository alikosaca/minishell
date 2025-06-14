/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 21:58:20 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/14 16:28:11 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_unset(t_env **env_list, char **args)
{
	int	i;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		remove_env(env_list, args[i]);
		i++;
	}
	return (0);
}
