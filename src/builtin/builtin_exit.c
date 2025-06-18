/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 09:29:57 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/18 03:11:21 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	builtin_exit(char **args)
{
	int	j;

	printf("exit\n");
	if (!args[1])
		exit(0);
	j = -1;
	while (args[1][++j])
		if (!ft_isdigit(args[1][j]))
			exit(error("exit", args[1], ERR_NUM_ARG_REQ, 2));
	if (args[2])
		exit(error("exit", NULL, ERR_TOO_MANY_ARGS, 1));
	exit(ft_atoi(args[1]) % 256);
}
