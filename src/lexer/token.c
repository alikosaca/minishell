/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:36:47 by akosaca           #+#    #+#             */
/*   Updated: 2025/08/16 21:08:17 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*create_token(t_token_type type, char *value, bool merge)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	token->merge = merge;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*token;

	if (!tokens || !new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	token = (*tokens);
	while (token->next)
		token = token->next;
	token->next = new_token;
}

void	free_tokenlist(t_token **tokens)
{
	t_token	*tmp;

	while ((*tokens))
	{
		tmp = (*tokens)->next;
		if ((*tokens)->value)
			_free((void **)&(*tokens)->value);
		free((*tokens));
		(*tokens) = tmp;
	}
}
