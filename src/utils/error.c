/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:03:04 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/02 19:11:37 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

int	cmd_err(t_shell *shell, char *cmd, char *opt, char *msg)
{
	ft_putstr_fd(BASH, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (opt)
	{
		ft_putstr_fd(opt, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	else if (opt && ft_strcmp(cmd, "export") == 0)
	{
		ft_putstr_fd("`", STDERR_FILENO);
		ft_putstr_fd(opt, STDERR_FILENO);
		ft_putstr_fd("'", STDERR_FILENO);
	}
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (shell->exitcode);
}

int	lx_err(t_shell *shell, char *msg, char *sep)
{
	ft_putstr_fd(BASH, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(" `", STDERR_FILENO);
	ft_putstr_fd(sep, STDERR_FILENO);
	ft_putstr_fd("'", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	shell->exitcode = 2;
	return (shell->exitcode);
}
