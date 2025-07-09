/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 09:29:57 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/09 19:52:17 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

int	builtin_exit(t_shell *shell, char **argv)
{
	int	j;

	printf("exit\n");
	if (!argv[1])
		exit(0);
	j = -1;
	while (argv[1][++j])
		if (!ft_isdigit(argv[1][j]))
			exit(cmd_err(shell, "exit", ERR_NUM_ARG_REQ, 2));
	if (argv[2])
		return (cmd_err(shell, "exit", ERR_TOO_MANY_ARGS, 1));
	shell->exitcode = ft_atoi(argv[1]) % 256;
	exit(shell->exitcode);
}
