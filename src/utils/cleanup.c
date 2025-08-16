/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:29:43 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/16 21:09:48 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	cleanup(t_shell *shell)
{
	if (shell->input)
		_free((void **)&shell->input);
	if (shell->envlist)
		free_envlist(&shell->envlist);
	if (shell->tokens)
		free_tokenlist(&shell->tokens);
	if (shell->commands)
		free_cmdlist(&shell->commands);
	close(shell->stdin_backup);
	close(shell->stdout_backup);
}
