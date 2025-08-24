/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:08:24 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/24 14:02:38 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "libft.h"
# include "structs.h"
# include "env.h"
# include "lexer.h"
# include "parser.h"

# define PROMPT "minishell$ "

# define BASH "bash: "
# define ERR_SYNTAX "syntax error near unexpected token"
# define ERR_NO_SUCH_FILE_OR_DIR "No such file or directory"

int		init_shell(t_shell *shell);

void	_free(void **ptr);
void	__free(void ***ptr);

void	cleanup(t_shell *shell);

int		cmd_err(t_shell *shell, char *cmd, char *msg, int ret);
int		opt_err(t_shell *shell, char *opt, char *msg, int ret);
int		lx_err(t_shell *shell, char *sep);

#endif
