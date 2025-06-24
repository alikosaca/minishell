/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:35:26 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/24 18:46:45 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

int	is_redir(t_token_type type)
{
	return (type == T_REDIRECT_IN
		|| type == T_REDIRECT_OUT
		|| type == T_REDIRECT_APPEND
		|| type == T_HEREDOC);
}

int	is_word_like(t_token_type type)
{
	return (type == T_WORD
		|| type == T_SINGLE_QUOTE
		|| type == T_DOUBLE_QUOTE
		|| type == T_DOLLAR);
}

int	syntax(t_token *token)
{
	if (token && !token->next)
		if (token->type == T_PIPE || is_redir(token->type))
			return (error_syntax(ERR_SYNTAX, token->value, 2));
	if (token && token->next && !token->next->next)
	{
		if (token->type == T_PIPE)
			return (error_syntax(ERR_SYNTAX, token->value, 2));
		else if (token->next->type == T_PIPE)
			return (error_syntax(ERR_SYNTAX, token->next->value, 2));
	}
	while (token)
	{
		if (token->type == T_ERROR)
			return (error_syntax(ERR_SYNTAX, token->value, 2));
		if (is_redir(token->type))
		{
			if (!token->next || !is_word_like(token->next->type))
				return (error_syntax(ERR_SYNTAX, token->value, 2));
		}
		if (!token->next && (token->type == T_PIPE || is_redir(token->type)))
			return (error_syntax(ERR_SYNTAX, token->value, 2));
		token = token->next;
	}
	return (0);
}
