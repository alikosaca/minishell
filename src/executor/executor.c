/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 09:50:12 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/18 19:45:51 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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
	if (cmd->next)
		shell->exitcode = exec_pipeline(shell, cmd);
	else
	{
		if (!cmd->argv && cmd->redirects)
		{
			if (setup_redir(shell, cmd))
			{
				if (restore_std_fds(shell))
					return (shell->exitcode);
				return (shell->exitcode);
			}
		}
		else if (cmd->argv)
			return (exec_cmd(shell, cmd));
	}
	if (restore_std_fds(shell))
		return (shell->exitcode);
	return (shell->exitcode);
}
