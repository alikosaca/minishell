/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:46:03 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/27 11:34:33 by yaycicek         ###   ########.fr       */
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

void	init_shell(t_shell *shell, char **envp);
void	cleanup(t_shell *shell);
int		syntax(t_token *tokens);

#endif
