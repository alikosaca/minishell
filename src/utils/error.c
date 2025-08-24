/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:03:04 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/24 14:07:30 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	cmd_err(t_shell *shell, char *cmd, char *msg, int ret)
{
	if (ret != 127 && ret != 2)
		ft_putstr_fd(BASH, STDERR_FILENO);
	if (ret == 127 && ft_strcmp(msg, ERR_NO_SUCH_FILE_OR_DIR) == 0)
		ft_putstr_fd(BASH, STDERR_FILENO);
	if (ret == 2 && ft_strcmp(cmd, ".") == 0)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd("usage", STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		shell->exitcode = ret;
		return (shell->exitcode);
	}
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	shell->exitcode = ret;
	return (shell->exitcode);
}

int	opt_err(t_shell *shell, char *opt, char *msg, int ret)
{
	shell->exitcode = ret;
	ft_putstr_fd(BASH, STDERR_FILENO);
	if (ret == 2)
	{
		ft_putstr_fd("exit", STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(opt, STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("export", STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd("`", STDERR_FILENO);
		ft_putstr_fd(opt, STDERR_FILENO);
		ft_putstr_fd("'", STDERR_FILENO);
	}
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (shell->exitcode);
}

int	lx_err(t_shell *shell, char *sep)
{
	ft_putstr_fd(BASH, STDERR_FILENO);
	ft_putstr_fd(ERR_SYNTAX, STDERR_FILENO);
	ft_putstr_fd(" `", STDERR_FILENO);
	ft_putstr_fd(sep, STDERR_FILENO);
	ft_putstr_fd("'", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	shell->exitcode = 2;
	return (shell->exitcode);
}
