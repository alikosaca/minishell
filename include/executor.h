/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:43:22 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/02 18:25:15 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "structs.h"
# include "utils.h"
# include "builtin.h"

# define ERR_CMD_NOT_FOUND "command not found"

int	executor(t_shell *shell, t_cmd *cmd);

int	is_builtin(char *cmd);
int	exec_builtin(t_shell *shell, char **argv);

#endif
