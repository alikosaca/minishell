/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:08:24 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/02 00:32:06 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "structs.h"
# include "../libft/libft.h"

# define BASH "bash"

# define ERR_SYNTAX "syntax error near unexpected token"

int		cmd_err(t_shell *shell, char *cmd, char *msg, int ret);
int		lx_err(t_shell *shell, char *sep);

void	_free(char **ptr);
void	__free(char ***ptr);

#endif
