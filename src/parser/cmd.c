/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:15:55 by akosaca           #+#    #+#             */
/*   Updated: 2025/07/31 14:42:03 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

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
