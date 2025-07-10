/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:15:55 by akosaca           #+#    #+#             */
/*   Updated: 2025/07/10 17:34:35 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	add_to_argv(t_arglist *args, char *value)
{
	char	**tmp;

	tmp = realloc(args->argv, sizeof(char *) * (args->argc + 2));
	if (!tmp)
		return (1);

	args->argv = tmp;
	args->argv[args->argc++] = value;
	args->argv[args->argc] = NULL;

	return (0);
}

int	add_to_redirect(t_redirect **redirects, t_redirect **head, t_token **tokens)
{
	t_redirect	*new_redir;

	new_redir = init_redirect();
	if (!new_redir)
		return (1);
	new_redir->type = redirect_type((*tokens)->type);
	*tokens = (*tokens)->next;
	if ((*tokens)->type == T_WORD && new_redir->type == REDIR_HEREDOC)
	new_redir->delimiter = (*tokens)->value;
	else if ((*tokens)->type == T_WORD)
	new_redir->file = (*tokens)->value;
	
	if (!(*head))
	{
		*head = new_redir;
		*redirects = new_redir;
	}
	else
	{
		(*redirects)->next = new_redir;
		*redirects = (*redirects)->next;
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


int	add_cmd(t_cmd **cmd, t_redirect *redir, char **argv)
{
	t_cmd	*new_cmd;
	t_cmd	*last_cmd;

	new_cmd = init_cmd(redir, argv);
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

t_cmd	*init_cmd(t_redirect *redir, char **argv)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = argv;
	cmd->redirects = redir;
	cmd->next = NULL;

	return (cmd);
}

void	free_redirlist(t_redirect *redir)
{
	t_redirect	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir)
			free(redir);
		redir = tmp;
	}
}

void	free_cmdlist(t_cmd **cmd)
{
	t_cmd	*tmp;

	while (*cmd)
	{
		tmp = (*cmd)->next;
		if ((*cmd)->redirects)
			free_redirlist((*cmd)->redirects);
		free(*cmd);
		(*cmd) = tmp;
	}
}
