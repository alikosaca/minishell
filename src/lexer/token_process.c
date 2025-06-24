/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:41:20 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/24 15:02:55 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

int	process_errors(t_token **tokens, char **input)
{
	int		len;
	char	*value;

	len = check_e_sequence(*input);
	if (len > 0)
	{
		value = malloc(len + 1);
		ft_memcpy(value, *input, len);
		value[len] = '\0';
		add_token(tokens, create_token(T_ERROR, value));
		*input += len;
		return (1);
	}
	return (0);
}


int	process_redirection(t_token **tokens, char **input)
{
	if (**input == '<' && *(*input + 1) == '<')
	{
		add_token(tokens, create_token(T_HEREDOC, "<<"));
		*input += 2;
		return (1);
	}
	else if (**input == '>' && *(*input + 1) == '>')
	{
		add_token(tokens, create_token(T_REDIRECT_APPEND, ">>"));
		*input += 2;
		return (1);
	}
	else if (**input == '<')
	{
		add_token(tokens, create_token(T_REDIRECT_IN, "<"));
		(*input)++;
		return (1);
	}
	else if (**input == '>')
	{
		add_token(tokens, create_token(T_REDIRECT_OUT, ">"));
		(*input)++;
		return (1);
	}
	return (0);
}

int	process_operator(t_token **tokens, char **input)
{
	if (**input == '|' && *(*input + 1) != '|')
	{
		add_token(tokens, create_token(T_PIPE, "|"));
		(*input)++;
		return (1);
	}
	return (0);
}

int	process_quote(t_token **tokens, char **input)
{
	char	*value;
	char	*start;

	if (**input == '\'' || **input == '"')
	{
		start = *input;
		value = handle_quote(input);
		if (!value)
		{
			add_token(tokens, create_token(T_ERROR, start));
			return (1);
		}
		else if (*start == '\'')
			add_token(tokens, create_token(T_SINGLE_QUOTE, value));
		else
			add_token(tokens, create_token(T_DOUBLE_QUOTE, value));
		return (1);
	}
	return (0);
}

int	process_dollar_or_word(t_token **tokens, char **input)
{
	char	*value;

	if (**input == '$')
	{
		value = handle_dollar(input);
		if (!value)
		{
			add_token(tokens, create_token(T_ERROR, "$"));
			return (1);
		}
		add_token(tokens, create_token(T_DOLLAR, value));
		return (1);
	}
	else
	{
		value = handle_word(input);
		if (value)
		{
			add_token(tokens, create_token(T_WORD, value));
			return (1);
		}
	}
	return (0);
}
