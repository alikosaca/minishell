/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:08:24 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/12 11:20:01 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "structs.h"
# include "env.h"
# include "lexer.h"
# include "parser.h"
# include "../libft/libft.h"

# define PROMPT "minishell$ "

# define BASH "bash"
# define ERR_SYNTAX "syntax error near unexpected token"

int		init_shell(t_shell *shell);

void	_free(void **ptr);
void	__free(void ***ptr);

void	cleanup(t_shell *shell);

int		cmd_err(t_shell *shell, char *cmd, char *msg, int ret);
int		exp_err(t_shell *shell, char *arg, char *msg, int ret);
int		lx_err(t_shell *shell, char *sep);

#endif
