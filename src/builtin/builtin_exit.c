/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 09:29:57 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/02 19:18:14 by yaycicek         ###   ########.fr       */
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
		{
			shell->exitcode = 2;
			exit(cmd_err(shell, "exit", argv[1], ERR_NUM_ARG_REQ));
		}
	if (argv[2])
	{
		shell->exitcode = 1;
		exit(cmd_err(shell, "exit", NULL, ERR_TOO_MANY_ARGS));
	}
	shell->exitcode = ft_atoi(argv[1]) % 256;
	exit(shell->exitcode);
}
