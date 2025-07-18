/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:43:48 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/18 19:15:38 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/expansion.h"

static void	adjust_heredoc_expansion(t_token **token)
{
	if ((*token)->type == T_SINGLE_QUOTE || (*token)->type == T_DOUBLE_QUOTE)
		(*token)->type = T_WORD; 
}

static void	handle_expansion(t_shell *shell, t_token *token)
{
	char	*expanded;

	expanded = NULL;
	if (!shell || !token)
		return ;
	if (token->type == T_DOLLAR)
		expanded = expand_dollar(shell, token->value);
	else if (token->type == T_DOUBLE_QUOTE)
		expanded = expand_dquote(shell, token->value); //!
	if (expanded)
		free(token->value);
	token->value = expanded;
}

static int	should_expand(t_token *token)
{
	if (!token)
		return (0);
	else if (token->type == T_DOLLAR)
		return (1);
	else if (token->type == T_DOUBLE_QUOTE && ft_strchr(token->value, '$'))
		return (1);
	return (0);
}

static void	change_token_type(t_token *token)
{
	if (token->type == T_SINGLE_QUOTE)
		token->type = T_WORD;
	else if (token->type == T_DOUBLE_QUOTE)
		token->type = T_WORD;
	else if (token->type == T_DOLLAR)
		token->type = T_WORD;
}

t_token	*expansion(t_shell *shell, t_token *tokens)
{
	t_token	*cur;
	t_token	*cur_merge;

	if (!shell || !tokens)
		return (NULL);
	cur = tokens;
	while (cur)
	{
		if (cur->type == T_HEREDOC && cur->next)
		{
			adjust_heredoc_expansion(&(cur->next));
			cur = cur->next->next;
			continue ;
		}
		if (should_expand(cur))
			handle_expansion(shell, cur);
		change_token_type(cur);
		cur = cur->next;
	}

	cur_merge = tokens;
	check_merge(&cur_merge);

	return (tokens);
}
