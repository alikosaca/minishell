/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:23:35 by akosaca           #+#    #+#             */
/*   Updated: 2025/05/28 19:36:11 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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

#endif
