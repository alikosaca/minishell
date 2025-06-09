/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:43:53 by akosaca           #+#    #+#             */
/*   Updated: 2025/06/09 13:16:53 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	process_tokens(char *input, t_token **tokens)
{
	t_token	*new_token;
	char	*value;

	while (*input)
	{
		if (!skip_whitespace(&input))
			break ;
		//! proccess these-> '<', '>', '|', '$', '"', '\''
	}
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	t_token	*new_token;
	char	*value;

	if (!input)
		return (NULL);
	tokens = NULL;
	proccess_tokens(input, &tokens);
	add_token(&tokens, create_token(TOKEN_EOF, NULL));
	return (tokens);
}
