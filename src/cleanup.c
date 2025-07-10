/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:29:43 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/10 17:06:52 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cleanup(t_shell *shell)
{
	if (shell->input)
		free(shell->input);
	if (shell->envlist)
		free_envlist(shell->envlist);
	if (shell->tokens)
		free_tokenlist(shell->tokens);
	if (shell->commands)
		free_cmdlist(shell->commands);
	if (shell->pids)
		free(shell->pids);
	close(shell->stdin_backup);
	close(shell->stdout_backup);
}
