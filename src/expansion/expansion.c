/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:43:48 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/27 12:40:59 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/expansion.h"

static char	*expand_dollar(t_shell *shell, char *key)
{
	char	*value;

	if (!shell || !key)
		return (NULL);
	key++;
	if (ft_strncmp(key, "?", 1) == 0)
		return (ft_itoa(shell->last_exit_code));
	value = get_env_value(shell->envlist, key);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static void	handle_expansion(t_shell *shell, t_token *token)
{
	char	*expanded;

	if (!shell || !token)
		return ;
	if (token->type == T_DOLLAR)
		expanded = expand_dollar(shell, token->value);
	// else if (token->type == T_DOUBLE_QUOTE)
	// 	expanded = expand_dquote(shell, token->value);
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
		cur = cur->next;
	}
	return (tokens);
}
