/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 09:50:12 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/09 19:35:48 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

int	executor(t_shell *shell, t_cmd *cmd)
{
	if (!shell || !cmd)
		return (0);
	while (cmd)
	{
		if (setup_redir(shell, cmd))
			return (shell->exitcode);
		if (is_builtin(cmd->argv[0]))
			shell->exitcode = exec_builtin(shell, cmd);
		else if (cmd->argv[0])
			shell->exitcode = exec_external(shell, cmd);
		if (restore_std_fds(shell))
			return (shell->exitcode);
		cmd = cmd->next;
	}
	return (shell->exitcode);
}
