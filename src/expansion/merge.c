/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:32:24 by akosaca           #+#    #+#             */
/*   Updated: 2025/08/20 12:29:07 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static t_token	*is_dollar(t_token *token)
{
	t_token	*merge;

	merge = token->next;
	if (token->value)
		_free((void **)&token->value);
	_free((void **)&token);
	return (merge);
}

t_token	*handle_merge(t_token *token)
{
	t_token	*merge;
	bool	new_merge;
	char	*val;

	if (token->type == T_DOLLAR)
		return (is_dollar(token));
	val = ft_strjoin(token->value, token->next->value);
	new_merge = token->next->merge;
	merge = create_token(T_WORD, val, new_merge);
	if (token->next->next)
		merge->next = token->next->next;
	else
		merge->next = NULL;
	if (token->value)
		_free((void **)&token->value);
	if (token->next->value)
		_free((void **)&token->next->value);
	_free((void **)&val);
	_free((void **)&token->next);
	_free((void **)&token);
	return (merge);
}

static void	connect_after_merge(t_token **head, t_token *prev, t_token *merged)
{
	if (prev)
		prev->next = merged;
	else
		*head = merged;
}

void	check_merge(t_token **token)
{
	t_token	*c;
	t_token	*prev;
	t_token	*merged;

	prev = NULL;
	c = *token;
	while (c && (c->type == T_DOLLAR || c->next))
	{
		if (c->type == T_HEREDOC)
		{
			c = c->next->next;
			continue ;
		}
		if (c->merge || c->type == T_DOLLAR)
		{
			merged = handle_merge(c);
			connect_after_merge(token, prev, merged);
			c = merged;
			continue ;
		}
		prev = c;
		c = c->next;
	}
}

// void	check_merge(t_token **token)
// {
// 	t_token	*c;
// 	t_token	*prev;
// 	t_token	*merged;

// 	prev = NULL;
// 	c = *token;
// 	while (c && (c->type == T_DOLLAR || c->next))
// 	{
// 		if (c->type == T_HEREDOC)
// 		{
// 			c = c->next->next;
// 			continue ;
// 		}
// 		if (c->merge || c->type == T_DOLLAR)
// 		{
// 			merged = handle_merge(c);
// 			if (prev)
// 				prev->next = merged;
// 			else
// 				*token = merged;
// 			c = merged;
// 		}
// 		else
// 		{
// 			prev = c;
// 			c = c->next;
// 		}
// 	}
// }
