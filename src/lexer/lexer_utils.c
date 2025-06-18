/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:36:47 by akosaca           #+#    #+#             */
/*   Updated: 2025/06/18 06:32:18 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	skip_whitespace(char **input)
{
	while (**input && is_whitespace(**input))
		(*input)++;
	if (**input)
		return (1);
	else
		return (0);
}

t_token	*create_token(t_token_type type, t_token **tokens, char *value)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		if (value)
			free(value);
		error_lexer(tokens);
	}
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*temp;

	temp = *tokens;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
}

void	error_lexer(t_token **tokens)
{
	t_token *tmp;

	if (!tokens || !*tokens)
		exit(error(NULL, NULL, ERR_SYNTAX, 1));
	while (*tokens)
	{
		tmp = (*tokens)->next;
		if ((*tokens)->value)
			free((*tokens)->value);
		free(*tokens);
		*tokens = tmp;
	}
	exit(error(NULL, NULL, ERR_SYNTAX, 1));
}