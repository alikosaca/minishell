/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:15:55 by akosaca           #+#    #+#             */
/*   Updated: 2025/07/17 19:28:13 by akosaca          ###   ########.fr       */
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
		{
			token = token->next->next;
		}
		else
		{
			token = token->next;
			i++;
		}
	}

	return (i);
}

int	init_argvlist(t_arglist **args, t_token *token)
{
	(*args)->argc = argc_len(token);
	(*args)->i = 0;
	(*args)->argv = malloc(sizeof(char *) * ((*args))->argc + 1);
	if (!(*args)->argv)
		return (1);
	return (0);
}

int	add_to_argv(t_arglist **args, char *value)
{
	(*args)->argv[(*args)->i] = value;
	(*args)->i++;
	(*args)->argv[(*args)->i] = NULL;

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
	{
		*cmd = new_cmd;
		// printf("add_cmd girdimmmmmmm \n");
		
		// if ((*cmd)->argv && (*cmd)->argv[0])
        //     printf("argv[0] = %s \n", (*cmd)->argv[0]);
        // else
        //     printf("argv[0] = NULL \n");
		
		// printf("add_cmd girdimmmmmmm \n");
	}
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
