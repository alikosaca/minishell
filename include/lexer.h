/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:23:35 by akosaca           #+#    #+#             */
/*   Updated: 2025/07/02 18:07:14 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include "structs.h"
# include "utils.h"
# include "structs.h"
# include "../libft/libft.h"

# define ERR_SYNTAX "syntax error near unexpected token"

t_token	*lexer(t_shell *shell, char *input);

void	skip_whitespace(char **input);
int		check_e_sequence(char *input);

t_token	*create_token(t_token_type type, char *value);
void	add_token(t_token **tokens, t_token *new_token);
void	free_tokenlist(t_token *tokens);

char	*handle_quote(char **input);
char	*handle_dollar(char **input);
char	*handle_word(char **input);

int		process_errors(t_token **tokens, char **input);
int		process_redirection(t_token **tokens, char **input);
int		process_operator(t_token **tokens, char **input);
int		process_quote(t_token **tokens, char **input);
int		process_dollar_or_word(t_token **tokens, char **input);

int		syntax(t_shell *shell, t_token *token);

#endif
