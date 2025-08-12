/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:03:04 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/12 11:22:08 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

int	cmd_err(t_shell *shell, char *cmd, char *msg, int ret)
{
	if (ret != 127)
	{
		ft_putstr_fd(BASH, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (msg)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	shell->exitcode = ret;
	return (shell->exitcode);
}

int	exp_err(t_shell *shell, char *arg, char *msg, int ret)
{
	ft_putstr_fd(BASH, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("export", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("`", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("'", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	shell->exitcode = ret;
	return (shell->exitcode);
}

int	lx_err(t_shell *shell, char *sep)
{
	ft_putstr_fd(BASH, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(ERR_SYNTAX, STDERR_FILENO);
	ft_putstr_fd(" `", STDERR_FILENO);
	ft_putstr_fd(sep, STDERR_FILENO);
	ft_putstr_fd("'", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	shell->exitcode = 2;
	return (shell->exitcode);
}
