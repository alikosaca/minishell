/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:41:20 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/20 18:01:47 by akosaca          ###   ########.fr       */
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
		add_token(tokens, create_token(T_ERROR, value, false));
		*input += len;
		return (1);
	}
	return (0);
}


int	process_redirection(t_token **tokens, char **input)
{
	if (**input == '<' && *(*input + 1) == '<')
	{
		add_token(tokens, create_token(T_HEREDOC, "<<", false));
		*input += 2;
		return (1);
	}
	else if (**input == '>' && *(*input + 1) == '>')
	{
		add_token(tokens, create_token(T_REDIRECT_APPEND, ">>", false));
		*input += 2;
		return (1);
	}
	else if (**input == '<')
	{
		add_token(tokens, create_token(T_REDIRECT_IN, "<", false));
		(*input)++;
		return (1);
	}
	else if (**input == '>')
	{
		add_token(tokens, create_token(T_REDIRECT_OUT, ">", false));
		(*input)++;
		return (1);
	}
	return (0);
}

int	process_operator(t_token **tokens, char **input)
{
	if (**input == '|' && *(*input + 1) != '|')
	{
		add_token(tokens, create_token(T_PIPE, "|", false));
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
			add_token(tokens, create_token(T_ERROR, start, false));
			return (1);
		}
		else if (*start == '\'')
			add_token(tokens, create_token(T_SINGLE_QUOTE, value, false));
		else
			add_token(tokens, create_token(T_DOUBLE_QUOTE, value, false));
		return (1);
	}
	return (0);
}
//printf(" \n");
int	process_dollar_or_word(t_token **tokens, char **input)
{
	char	*value;
	bool	merge;

	merge = false;
	if (**input == '$')
	{
		value = handle_dollar(input);
		if (**input && value && (**input != ' ' || **input != '\t'))
			merge = true;
		if (!value)
			add_token(tokens, create_token(T_ERROR, "$", merge));
		else
			add_token(tokens, create_token(T_DOLLAR, value, merge));
		return (1);
	}
	else
	{
		value = handle_word(input);
		if (!value)
			return (0);
		if (**input == '$')
			merge = true;
		add_token(tokens, create_token(T_WORD, value, merge));
	}
	return (1);
}
