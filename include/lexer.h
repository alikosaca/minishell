/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:23:35 by akosaca           #+#    #+#             */
/*   Updated: 2025/07/18 18:31:07 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include "structs.h"
# include "utils.h"
# include "structs.h"
# include "../libft/libft.h"

t_token	*lexer(t_shell *shell, char *input);

void	skip_whitespace(char **input);
int		check_e_sequence(char *input);

t_token	*create_token(t_token_type type, char *value, bool merge);
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
