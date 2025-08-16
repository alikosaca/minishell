/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 21:58:20 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/16 21:03:17 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_unset(t_shell *shell, char **argv)
{
	int	i;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		remove_env(&(shell->envlist), argv[i]);
		i++;
	}
	return (0);
}
