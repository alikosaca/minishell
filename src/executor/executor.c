/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 09:50:12 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/16 09:41:05 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

static int	prepare_all_heredocs(t_shell *shell, t_cmd *cmd)
{
	t_cmd	*it;

	it = cmd;
	while (it)
	{
		if (prepare_heredocs_for_cmd(shell, it->redirects))
			return (shell->exitcode);
		it = it->next;
	}
	return (0);
}

int	exec_cmd(t_shell *shell, t_cmd *cmd)
{
	if (!cmd->argv)
		return (setup_redir(shell, cmd));
	if (is_builtin(cmd))
		shell->exitcode = exec_builtin(shell, cmd);
	else
		shell->exitcode = exec_external(shell, cmd);
	if (restore_std_fds(shell))
		return (shell->exitcode);
	return (shell->exitcode);
}

int	executor(t_shell *shell, t_cmd *cmd)
{
	if (!shell || !cmd)
		return (0);
	shell->exitcode = 0;
	if (prepare_all_heredocs(shell, cmd))
		return (shell->exitcode);
	if (cmd->argv && !cmd->next)
		return (exec_cmd(shell, cmd));
	else if (cmd->argv && cmd->next)
		shell->exitcode = exec_pipeline(shell, cmd);
	if (restore_std_fds(shell))
		return (shell->exitcode);
	return (shell->exitcode);
}
