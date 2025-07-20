/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:32:24 by akosaca           #+#    #+#             */
/*   Updated: 2025/07/20 18:02:20 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expansion.h"

t_token	*handle_merge(t_token *token)
{
	t_token	*merge;
	bool	new_merge;
	char	*val;

	val = ft_strjoin(token->value, token->next->value);
	new_merge = token->next->merge;
	merge = create_token(T_WORD, val, new_merge);
	if (token->next->next)
		merge->next = token->next->next;
	else
		merge->next = NULL;
	if (token->value)
		free(token->value);
	if (token->next->value)
		free(token->next->value);
	free(token->next);
	free(token);

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
	
	while (current && current->next)
	{
		if (current->merge)
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







// void	check_merge(t_token **token)
// {
// 	t_token	*merge;
// 	t_token	*bf_token;

// 	if (!(*token) || !(*token)->next)
// 		return ;

// 	merge = NULL;
// 	bf_token = NULL;
// 	while (*token && (*token)->next)
// 	{
// 		if ((*token)->next->merge)
// 			bf_token = *token;
// 		if ((*token)->merge)
// 		{
// 			merge = handle_merge(*token);
// 			bf_token->next = merge;
// 			*token = merge;
// 		}
// 		else
// 			*token = (*token)->next;
// 	}
// }
