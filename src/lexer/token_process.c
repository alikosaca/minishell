/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:41:20 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/23 21:04:01 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

int	process_errors(t_token **tokens, char **input)
{
	int		len;
	char	*value;

	len = check_error_sequence(*input);
	if (len > 0)
	{
		value = malloc(len + 1);
		ft_memcpy(value, *input, len);
		value[len] = '\0';
		add_token(tokens, create_token(T_ERROR, value));
		*input += len;
		return (1);
	}
	if (is_error_char(**input))
	{
		value = malloc(2);
		value[0] = **input;
		value[1] = '\0';
		add_token(tokens, create_token(T_ERROR, value));
		(*input)++;
		return (1);
	}
	return (0);
}

int	process_redirection(t_token **tokens, char **input)
{
	if (**input == '<' && *(*input + 1) == '<')
	{
		add_token(tokens, create_token(T_HEREDOC, ft_strdup("<<")));
		*input += 2;
		return (1);
	}
	else if (**input == '>' && *(*input + 1) == '>')
	{
		add_token(tokens, create_token(T_REDIRECT_APPEND, ft_strdup(">>")));
		*input += 2;
		return (1);
	}
	else if (**input == '<')
	{
		add_token(tokens, create_token(T_REDIRECT_IN, ft_strdup("<")));
		(*input)++;
		return (1);
	}
	else if (**input == '>')
	{
		add_token(tokens, create_token(T_REDIRECT_OUT, ft_strdup(">")));
		(*input)++;
		return (1);
	}
	return (0);
}

int	process_operator(t_token **tokens, char **input)
{
	if (**input == '|' && *(*input + 1) != '|')
	{
		add_token(tokens, create_token(T_PIPE, ft_strdup("|")));
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
			add_token(tokens, create_token(T_ERROR, ft_strdup(start)));
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
			add_token(tokens, create_token(T_ERROR, ft_strdup("$")));
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
