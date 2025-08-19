/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:32:24 by akosaca           #+#    #+#             */
/*   Updated: 2025/08/19 13:11:50 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

t_token	*handle_merge(t_token *token)
{
	t_token	*merge;
	bool	new_merge;
	char	*val;

	if (token->type == T_DOLLAR)
	{
		merge = token->next;
		_free((void **)&token);
		return (merge);
	}
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

void	check_merge(t_token **token)
{
	t_token	*current;
	t_token	*prev;
	t_token	*merged;

	if (!token || !*token)
		return ;
	prev = NULL;
	current = *token;
	while (current && (current->type == T_DOLLAR || current->next))
	{
		if (current->merge || current->type == T_DOLLAR)
		{
			merged = handle_merge(current);
			if (prev)
				prev->next = merged;
			else
				*token = merged;
			current = merged;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}
