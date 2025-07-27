/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:00:02 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/27 11:30:17 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

int	is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_shell *shell, t_cmd *cmd)
{
	if (!shell || !cmd->argv || !cmd->argv[0])
		return (1);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(cmd->argv));
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (builtin_cd(shell, cmd->argv));
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (builtin_pwd(shell));
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (builtin_export(shell, cmd->argv));
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (builtin_unset(shell, cmd->argv));
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (env(shell->envlist, cmd->argv));
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (builtin_exit(shell, cmd->argv));
	return (shell->exitcode);
}
