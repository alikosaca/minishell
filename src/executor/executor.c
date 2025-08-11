/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 09:50:12 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/11 14:59:00 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

int	executor(t_shell *shell, t_cmd *cmd)
{
	if (!shell || !cmd)
		return (0);
	if (!cmd->argv)
		if (setup_redir(shell, cmd))
			return (shell->exitcode);
	if (cmd->argv && !cmd->next)
	{
		if (is_builtin(cmd))
			shell->exitcode = exec_builtin(shell, cmd);
		else
			shell->exitcode = exec_external(shell, cmd);
	}
	else if (cmd->argv && cmd->next)
		shell->exitcode = exec_pipeline(shell, cmd);
	if (restore_std_fds(shell))
		return (shell->exitcode);
	return (shell->exitcode);
}
