/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:16:25 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/29 22:42:14 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

int	restore_std_fds(t_shell *shell)
{
	if (dup2(shell->stdin_backup, STDIN_FILENO) == -1)
		return (cmd_err(shell, "dup2", strerror(errno), 1));
	if (dup2(shell->stdout_backup, STDOUT_FILENO) == -1)
		return (cmd_err(shell, "dup2", strerror(errno), 1));
	return (0);
}

int	restore_doc_fds(t_shell *shell, int fd[2], bool should_dup)
{
    close(fd[1]);
    if (should_dup)
    {
        if (dup2(fd[0], STDIN_FILENO) == -1)
        {
            close(fd[0]);
            return (cmd_err(shell, "dup2", strerror(errno), 1));
        }
    }
    close(fd[0]);
    return (0);
}
