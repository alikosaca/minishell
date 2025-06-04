/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:23:35 by akosaca           #+#    #+#             */
/*   Updated: 2025/06/04 18:54:35 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_token_type
{
	TOKEN_WORD,				//normal kelimeler: ls, cat, file.txt
	TOKEN_PIPE,				// |
	TOKEN_REDIRECT_IN,		// <
	TOKEN_REDIRECT_OUT,		// >
	TOKEN_REDIRECT_APPEND,	// >>
	TOKEN_HEREDOC,			// <<
	TOKEN_SINGLE_QUOTE,		// 'text'
	TOKEN_DOUBLE_QUOTE,		// "text"
	TOKEN_ENV_VAR,			// $HOME, $USER
	TOKEN_EOF,				// input sonu
	TOKEN_ERROR,			// hatalı token
}			t_token_type;

typedef struct s_token
{
	t_token_type	type;	// token türü
	char			*value;	// token değeri
	struct s_token	*next;	// sonraki token
}				t_token;

// Boşluk var mı kontrol et varsa is_whitespace ile boşlukları atla
int		skip_whitespace(char **input);

//Boşlukları atla
int		is_whitespace(char c);

// Özel karakterleri kontrol et
int		is_special_char(char c);

// Boşlukları atla

void	add_token(t_token **tokens, t_token *new_token);
void	free_tokens(t_token *tokens);

char	*extract_word(char **input);
char	*extract_quoted_string(char **input, char quote);
char	*extract_env_var(char **input);

t_token	*process_redirect(char **input);
t_token	*create_token(t_token_type type, char *value);


t_token		*lexer(char *input);
t_token		*create_token(t_token_type type, char *value);
void		add_token(t_token **tokens, t_token *new_token);
void		free_tokens(t_token *tokens);

#endif
