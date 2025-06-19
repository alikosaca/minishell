/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:23:35 by akosaca           #+#    #+#             */
/*   Updated: 2025/06/19 11:46:00 by yaycicek         ###   ########.fr       */
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
	T_WORD,				//normal kelimeler: ls, cat, file.txt
	T_PIPE,				// |
	T_REDIRECT_IN,		// <
	T_REDIRECT_OUT,		// >
	T_REDIRECT_APPEND,	// >>
	T_HEREDOC,			// <<
	T_SINGLE_QUOTE,		// 'text'
	T_DOUBLE_QUOTE,		// "text"
	T_DOLLAR,			// $HOME, $USER
	T_EOF,				// input sonu
	T_ERROR,			// hatalı token
}			t_token_type;

typedef struct s_token
{
	t_token_type	type;	// token türü
	char			*value;	// token değeri
	struct s_token	*next;	// sonraki token
}				t_token;

int	is_whitespace(char c);
int	skip_whitespace(char **input);

void	error_lexer(t_token **tokens);
void	handle_word(t_token **tokens, char **input);
void	add_token(t_token **tokens, t_token *new_token);
void	add_op(t_token_type type, t_token **tokens, char **input, char *val);
void	handle_string_literal(t_token_type type, t_token **tokens, char **input, char *val);

t_token	*lexer(char *input);
t_token	*create_token(t_token_type type, t_token **tokens, char *value);

#endif
