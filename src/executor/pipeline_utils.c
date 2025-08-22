/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:30:57 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/22 17:21:25 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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
		close(pipefd[0]);
		close(pipefd[1]);
		cmd_err(shell, "fork", strerror(errno), 254);
		return (-1);
	}
	return (pid);
}

void	check_invalid(t_shell *shell, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "."))
	{
		cmd_err(shell, cmd->argv[0], ERR_FILENAME_REQUIRED, 0);
		cmd_err(shell, cmd->argv[0], ERR_DOT_SYNTAX, 2);
	}
	else if (!ft_strcmp(cmd->argv[0], "\0"))
		cmd_err(shell, "''", ERR_CMD_NOT_FOUND, 127);
	if (shell->exitcode == 2 || shell->exitcode == 127)
	{
		cleanup(shell);
		exit(shell->exitcode);
	}
}

void	wait_all_children(t_shell *shell, pid_t *pids, int child_count)
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
					ft_putstr_fd("\n", STDOUT_FILENO);
				else if (WTERMSIG(status) == SIGQUIT)
					ft_putendl_fd(MSG_SIGQUIT, STDERR_FILENO);
				shell->exitcode = 128 + WTERMSIG(status);
			}
			else if (WIFEXITED(status))
				shell->exitcode = WEXITSTATUS(status);
		}
		i++;
	}
}
