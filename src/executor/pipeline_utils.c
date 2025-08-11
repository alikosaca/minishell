/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:30:57 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/11 15:33:36 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

pid_t	create_process(t_shell *shell, t_cmd *cmd, int pipefd[2])
{
	pid_t	pid;

	if (cmd->next && pipe(pipefd) == -1)
	{
		cmd_err(shell, "pipe", strerror(errno), 1);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		cmd_err(shell, "fork", strerror(errno), 1);
		return (-1);
	}
	return (pid);
}

int	wait_all_children(t_shell *shell, pid_t *pids, int child_count)
{
	int	status;
	int	i;

	i = 0;
	while (i < child_count)
	{
		if (waitpid(pids[i], &status, 0) == -1)
			break ;
		if (child_count - 1 == i)
		{
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					printf("\n");
				shell->exitcode = 128 + WTERMSIG(status);
			}
			else if (WIFEXITED(status))
				shell->exitcode = WEXITSTATUS(status);
		}
		i++;
	}
	return (shell->exitcode);
}
