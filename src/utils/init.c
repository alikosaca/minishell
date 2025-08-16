/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:25:58 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/16 21:09:59 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	init_shell(t_shell *shell)
{
	shell->prompt = PROMPT;
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
	if (shell->stdin_backup == -1 || shell->stdout_backup == -1)
		return (cmd_err(shell, "dup", strerror(errno), 1));
	return (0);
}
