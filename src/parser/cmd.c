/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:15:55 by akosaca           #+#    #+#             */
/*   Updated: 2025/07/09 20:58:48 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

// int	argv_len(t_token *token)
// {
// 	int		i;

// 	i = 0;
// 	if (!token)
// 		return (0);
// 	while (token->type == T_WORD)
// 	{
// 		i++;
// 		token = token->next;
// 	}
// 	return (i);
// }
//len = argv_len(tokens);



// char	**add_to_argv(char *value)
// {
// 	char **argv;
// 	int	i;
// 	int len;

// 	if (!len)
// 		return (NULL);
// 	argv = malloc(sizeof(char *));
// 	if (!argv)
// 		return (NULL);
// 	i = 0;
// 	while (token->type == T_WORD)
// 	{
// 		argv[i++] = token->value;
// 		token = token->next;
// 	}
// 	argv[i] = NULL;

// 	return (argv);
// }


//*-------------------------------------------------------------------------*//

int	add_to_argv(char **argv, int *argc, char *value)
{
	
	char	**tmp;
	int		i;

	if (!(*argv))
		i = 2;
	else
		i = 1;
	tmp = realloc(argv, sizeof(char *) * (*argc + i));
	if (!tmp)
		return (1);	
	argv = tmp;
	argv[(*argc)++] = value;
	argv[(*argc)] = NULL;

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
		return (0);
	}
	last_cmd = *cmd;
	while (last_cmd->next)
		last_cmd = last_cmd->next;
	last_cmd->next = new_cmd;

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
	redir = NULL;
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
