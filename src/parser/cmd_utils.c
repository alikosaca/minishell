/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:37:34 by akosaca           #+#    #+#             */
/*   Updated: 2025/08/05 13:44:59 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	argc_len(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type != T_PIPE)
	{
		if (is_redirect(token->type) && token->next)
				token = token->next->next;
		else if (ft_strlen(token->value) == 0)
			token = token->next;
		else
		{
			token = token->next;
			i++;
		}
	}
	return (i);
}

int	add_to_argv(t_cmd **new_cmd, char *value)
{
	if (ft_strlen(value) != 0)
	{
		(*new_cmd)->argv[(*new_cmd)->i] = value;
		(*new_cmd)->i++;
		(*new_cmd)->argv[(*new_cmd)->i] = NULL;
	}
	return (0);
}

static void	set_redir_values(t_redirect **redir, t_token *tokens, bool stat)
{
	if (stat && (tokens->type == T_WORD || tokens->type == T_DOLLAR))
	{
		(*redir)->delimiter = tokens->value;
		(*redir)->should_be_expand = true;
	}
	else if (stat)
		(*redir)->delimiter = tokens->value;
	else
		(*redir)->file = tokens->value;
}

int	add_to_redirect(t_redirect **redir, t_token **tokens)
{
	t_redirect	*new_redir;
	t_redirect	*last_redir;

	last_redir = (*redir);
	new_redir = init_redirect();
	if (!new_redir)
		return (1);
	new_redir->type = redirect_type((*tokens)->type);
	*tokens = (*tokens)->next;
	if (new_redir->type == REDIR_HEREDOC)
		set_redir_values(&new_redir, *tokens, true);
	else
		set_redir_values(&new_redir, *tokens, false);
	if (!(*redir))
		*redir = new_redir;
	else
	{
		while (last_redir->next)
			last_redir = last_redir->next;
		last_redir->next = new_redir;
	}
	return (0);
}

int	add_cmd(t_cmd **cmd, t_cmd *new_cmd)
{
	t_cmd	*last_cmd;

	if (!new_cmd)
		return (1);
	if (!*cmd)
		*cmd = new_cmd;
	else
	{
		last_cmd = *cmd;
		while (last_cmd->next)
			last_cmd = last_cmd->next;
		last_cmd->next = new_cmd;
	}
	return (0);
}