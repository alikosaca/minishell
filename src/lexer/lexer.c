/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:43:53 by akosaca           #+#    #+#             */
/*   Updated: 2025/06/20 18:07:41 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

void	handle_word(t_token **tokens, char **input)
{
	const char	*start = *input;
	char		*word;
	int			len;

	len = 0;
	while (**input && !is_special_char(*input))
	{
		(*input)++;
		len++;
	}
	sntax_error_check(tokens, input );
	if (len == 0)
		return ;
	word = malloc(len + 1);
	if (!word)
		error_lexer(tokens);
	ft_memcpy(word, start, len);
	word[len] = '\0';
	add_token(tokens, create_token(T_WORD, tokens, word));
}

void	handle_string_literal(t_token_type type, t_token **tokens,
							char **input, char *val)
{
	const char	*start = ++(*input);
	char		*str;

	while (**input && **input != *val)
		(*input)++;
	if (**input != *val)
		error_lexer(tokens);
	str = malloc(*input - start + 1);
	if (!str)
		error_lexer(tokens);
	ft_memcpy(str, start, *input - start);
	str[*input - start] = '\0';
	add_token(tokens, create_token(type, tokens, val));
	add_token(tokens, create_token(T_WORD, tokens, str));
	add_token(tokens, create_token(type, tokens, val));
	(*input)++;
}

void	add_op(t_token_type type, t_token **tokens, char **input, char *val)
{
	add_token(tokens, create_token(type, tokens, val));
	if (type == T_PIPE || type == T_REDIRECT_IN || \
		type == T_REDIRECT_OUT || type == T_DOLLAR)
		(*input)++;
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
			add_op(T_HEREDOC, tokens, &input, "<<");
		else if (*input == '<')
			add_op(T_REDIRECT_IN, tokens, &input, "<");
		else if (*input == '>' && *(input + 1) == '>')
			add_op(T_REDIRECT_APPEND, tokens, &input, ">>");
		else if (*input == '>')
			add_op(T_REDIRECT_OUT, tokens, &input, ">");
		else if (*input == '|' && *(input + 1) != '|')
			add_op(T_PIPE, tokens, &input, "|");
		else if (*input == '\'')
			handle_string_literal(T_SINGLE_QUOTE, tokens, &input, "\'");
		else if (*input == '"')
			handle_string_literal(T_DOUBLE_QUOTE, tokens, &input, "\"");
		else if (*input == '$')
			add_op(T_DOLLAR, tokens, &input, "$");
		else
			handle_word(tokens, &input);
	}
}

t_token	*lexer(char *input)
{
	t_token	*tokens;

	if (!input)
		return (NULL);
	tokens = NULL;
	process_tokens(input, &tokens);
	add_token(&tokens, create_token(T_EOF, &tokens, NULL));
	return (tokens);
}
