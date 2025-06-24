/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:23:35 by akosaca           #+#    #+#             */
/*   Updated: 2025/06/24 15:12:55 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include "utils.h"
# include "../libft/libft.h"

# define ERR_SYNTAX "syntax error near unexpected token"

typedef enum e_token_type
{
	T_WORD,
	T_SINGLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_REDIRECT_APPEND,
	T_HEREDOC,
	T_PIPE,
	T_DOLLAR,
	T_ERROR			
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

t_token	*lexer(char *input);

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

#endif
