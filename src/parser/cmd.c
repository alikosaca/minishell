/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:15:55 by akosaca           #+#    #+#             */
/*   Updated: 2025/07/27 13:53:48 by akosaca          ###   ########.fr       */
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
		else
		{
			token = token->next;
			i++;
		}
	}
	return (i);
}

int	init_newcmd(t_cmd **new_cmd, t_token *token)
{
	(*new_cmd) = malloc(sizeof(t_cmd));
	if (!(*new_cmd))
		return (1);
	(*new_cmd)->argc = argc_len(token);
	(*new_cmd)->i = 0;
	(*new_cmd)->redirects = NULL;
	if ((*new_cmd)->argc == 0)
		(*new_cmd)->argv = NULL;
	else
		(*new_cmd)->argv = malloc(sizeof(char *) * ((*new_cmd)->argc + 1));
	(*new_cmd)->next = NULL;
	return (0);
}

int	add_to_argv(t_cmd **new_cmd, char *value)
{
	(*new_cmd)->argv[(*new_cmd)->i] = value;
	(*new_cmd)->i++;
	(*new_cmd)->argv[(*new_cmd)->i] = NULL;
	return (0);
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
	if (((*tokens)->type == T_WORD || ((*tokens)->type == T_DOLLAR))
		&& new_redir->type == REDIR_HEREDOC)
		new_redir->delimiter = (*tokens)->value;
	else if ((*tokens)->type == T_WORD)
		new_redir->file = (*tokens)->value;
	else if ((*tokens)->type == T_DOLLAR)
		new_redir->should_be_expand = true;
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
	
t_redirect	*init_redirect()
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->file = NULL;
	redir->delimiter = NULL;
	redir->should_be_expand = false;
	redir->next = NULL;
	return (redir);
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

void	free_redirlist(t_redirect *redir)
{
	t_redirect	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir);
		redir = tmp;
	}
}

void	free_cmdlist(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->redirects)
			free_redirlist(cmd->redirects);
		free(cmd);
		cmd = tmp;
	}
}
