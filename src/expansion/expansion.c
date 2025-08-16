/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:43:48 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/16 21:07:39 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static char	*expand_token(t_shell *shell, char *str, bool is_word)
{
	int		i;
	int		start;
	char	*res;
	char	*part;

	i = 0;
	res = ft_strdup("");
	while (check_expand_condition(str, &i, is_word))
	{
		if (str[i] == '$')
			part = parse_dollar(shell, str, &i);
		else
		{
			start = i;
			while (check_expand_condition(str, &i, is_word) && str[i] != '$')
				i++;
			part = ft_substr(str, start, i - start);
		}
		res = ft_strjoin_free_both(res, part);
	}
	return (res);
}

static void	handle_expansion(t_shell *shell, t_token *token)
{
	char	*expanded;

	expanded = NULL;
	if (!shell || !token)
		return ;
	if (token->type == T_DOLLAR)
		expanded = expand_token(shell, token->value, true);
	else if (token->type == T_DOUBLE_QUOTE)
		expanded = expand_token(shell, token->value, false);
	if (expanded)
		_free((void **)&token->value);
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

	if (!shell || !tokens)
		return (NULL);
	cur = tokens;
	while (cur)
	{
		if (cur->type == T_HEREDOC && cur->next)
		{
			cur = cur->next->next;
			continue ;
		}
		if (should_expand(cur))
			handle_expansion(shell, cur);
		change_token_type(cur);
		cur = cur->next;
	}
	check_merge(&tokens);
	return (tokens);
}
