/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:46:03 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/16 21:14:11 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>

# include "lexer.h"
# include "expansion.h"
# include "parser.h"
# include "executor.h"
# include "env.h"
# include "builtin.h"
# include "sig.h"
# include "utils.h"

# define PROMPT "minishell$ "

void	cleanup(t_shell *shell);

#endif
