/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 09:50:12 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/28 19:20:25 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

int	executor(t_shell *shell, t_cmd *cmd)
{
	if (!shell || !cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	while (cmd)
	{
		if (is_builtin(cmd->argv[0]))
			shell->exitcode = exec_builtin();
		else
			shell->exitcode = 127;
		cmd = cmd->next;
	}
	return (shell->exitcode);
}
