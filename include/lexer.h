/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:23:35 by akosaca           #+#    #+#             */
/*   Updated: 2025/06/04 10:47:00 by yaycicek         ###   ########.fr       */
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

#endif
