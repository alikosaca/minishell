/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:35:26 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/20 18:02:07 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

static int	is_redir(t_token_type type)
{
	return (type == T_REDIRECT_IN
		|| type == T_REDIRECT_OUT
		|| type == T_REDIRECT_APPEND
		|| type == T_HEREDOC);
}

static int	is_word_like(t_token_type type)
{
	return (type == T_WORD
		|| type == T_SINGLE_QUOTE
		|| type == T_DOUBLE_QUOTE
		|| type == T_DOLLAR);
}

int	syntax(t_shell *shell, t_token *token)
{
	if (token && !token->next)
	if (token->type == T_PIPE || is_redir(token->type))
	return(lx_err(shell, token->value)); 
	if (token && token->next && !token->next->next)
	{
		if (token->type == T_PIPE)
			return (lx_err(shell, token->value));
		else if (token->next->type == T_PIPE)
			return (lx_err(shell, token->next->value));
	}
	while (token)
	{
		if (token->type == T_ERROR)
			return (lx_err(shell, token->value));
		if (is_redir(token->type))
		{
			if (!token->next || !is_word_like(token->next->type))
				return (lx_err(shell, token->value));
		}
		if (!token->next && (token->type == T_PIPE || is_redir(token->type)))
			return (lx_err(shell, token->value));
		token = token->next;
	}
	return (0);
}
