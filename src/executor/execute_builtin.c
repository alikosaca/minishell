/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:00:02 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/28 18:23:54 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_shell *shell, t_cmd *cmd)
{
	if (!shell || !cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(NULL));
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (builtin_cd(NULL, NULL));
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (builtin_export(NULL, NULL));
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (builtin_unset(NULL, NULL));
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (builtin_env(NULL));
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (builtin_exit(NULL));
}
