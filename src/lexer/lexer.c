/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:43:53 by akosaca           #+#    #+#             */
/*   Updated: 2025/06/14 20:12:38 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_operator(t_token_type type, t_token **tokens, char **input, char *val)
{
	t_token	*token;

	token = create_token(T_PIPE, ft_strdup(val));
	add_token(tokens, token);
	if (type == T_PIPE || type == T_REDIRECT_IN || type == T_REDIRECT_OUT)
		*input++;
	else if (type == T_HEREDOC || type == T_REDIRECT_APPEND)
		*input = *input + 2;
}

static void	process_tokens(char *input, t_token **tokens)
{
	while (*input)
	{
		if (!skip_whitespace(&input))
			break ;
		else if (*input == '<' && *(input + 1) == '<')
				handle_operator(T_HEREDOC, tokens, &input, "<<");
		else if (*input == '<')
				handle_operator(T_REDIRECT_IN, tokens, &input, "<");
		else if (*input == '>' && *(input + 1) == '>')
				handle_operator(T_REDIRECT_APPEND, tokens, &input, ">>");
		else if (*input == '>')
				handle_operator(T_REDIRECT_OUT, tokens, &input, ">");
		else if (*input == '|')
			handle_operator(T_PIPE, tokens, &input, "|");
		// else if (*input == '\'')
		// 	handle_single_quote(tokens, &input);
		// else if (*input == '"')
		// 	handle_double_quote(tokens, &input);
		// else if (*input == '$')
		// 	handle_env_var(tokens, &input);
		// else
		// 	handle_word(tokens, &input);
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
	process_tokens(input, &tokens);
	add_token(&tokens, create_token(T_EOF, NULL));
	return (tokens);
}
