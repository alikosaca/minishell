/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 09:29:57 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/24 14:14:27 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_exit(t_shell *shell, char **argv)
{
	int	j;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (!argv[1])
	{
		cleanup(shell);
		exit(0);
	}
	j = -1;
	while (argv[1][++j])
	{
		if (argv[1][j] == '+' || argv[1][j] == '-')
			j++;
		if (!ft_isdigit(argv[1][j]))
		{
			opt_err(shell, argv[1], ERR_NUM_ARG_REQ, 2);
			cleanup(shell);
			exit(shell->exitcode);
		}
	}
	if (argv[2])
		return (cmd_err(shell, "exit", ERR_TOO_MANY_ARGS, 1));
	shell->exitcode = ft_atoi(argv[1]) % 256;
	cleanup(shell);
	exit(shell->exitcode);
}
