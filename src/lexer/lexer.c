/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:43:53 by akosaca           #+#    #+#             */
/*   Updated: 2025/08/16 21:07:55 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	process_tokens(char *input, t_token **tokens)
{
	while (*input)
	{
		skip_whitespace(&input);
		if (!*input)
			break ;
		if (process_errors(tokens, &input))
			continue ;
		if (process_redirection(tokens, &input))
			continue ;
		if (process_operator(tokens, &input))
			continue ;
		if (process_quote(tokens, &input))
			continue ;
		if (process_dollar_or_word(tokens, &input))
			continue ;
	}
}

t_token	*lexer(t_shell *shell, char *input)
{
	t_token	*tokens;

	if (!input || !(*input))
		return (NULL);
	tokens = NULL;
	process_tokens(input, &tokens);
	if (syntax(shell, tokens) == 2)
	{
		free_tokenlist(&tokens);
		return (NULL);
	}
	return (tokens);
}
