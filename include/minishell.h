/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:46:03 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/02 15:50:44 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>

# include "env.h"
# include "builtin.h"
# include "signal.h"
# include "utils.h"
# include "lexer.h"
# include "expansion.h"
# include "parser.h"
# include "executor.h"

# define PROMPT "minishell$ "

int		init_shell(t_shell *shell);
void	cleanup(t_shell *shell);

#endif
