/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:15:55 by akosaca           #+#    #+#             */
/*   Updated: 2025/07/06 19:23:42 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	argv_len(t_token *token)
{
	int		i;

	i = 0;
	if (!token)
		return (0);
	while (token->type == T_WORD)
	{
		i++;
		token = token->next;
	}
	return (i);
}
//len = argv_len(tokens);

char	**add_to_argv(char *value)
{
	char **argv;
	int	i;
	int len;

	if (!len)
		return (NULL);
	argv = malloc(sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	while (tokens->type == T_WORD)
	{
		argv[i++] = tokens->value;
		tokens = tokens->next;
	}
	argv[i] = NULL;

	return (argv);
}

t_cmd	*init_cmd(t_cmd **cmd)
{
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	(*cmd)->argv = NULL;
	(*cmd)->redirects = NULL;
	(*cmd)->next = NULL;
	return (cmd);
}

t_redirect	*add_to_redirect(t_token *tokens)
{
	t_redirect	*redir;

	redir = init_redirect(redir);
	if (!redir)
		return (NULL);
	redir->type = redirect_type(tokens->type);
	tokens = tokens->next;
	if (tokens->type == T_WORD && redir->type == REDIR_HEREDOC)
		redir->delimiter = tokens->value;
	else if (tokens->type == T_WORD)
		redir->file = tokens->value;
	tokens = tokens->next;
	return (redir);
}

// t_redirect	*add_to_redirect(t_token *tokens)
// {
// 	t_redirect	*redir;
// 	t_redirect	*first_redir;

// 	//redir = malloc(sizeof(t_redirect *));
// 	//first_redirect = cmd->redirects;
// 	while (is_redirect(tokens->type) && tokens->next->type == T_WORD)
// 	{
// 		redir = init_redirect(redir);
// 		if (!redir)
// 			return (NULL);
// 		redir->type = redirect_type(tokens->type);
// 		tokens = tokens->next;
// 		if (tokens->type == T_WORD && redir->type == REDIR_HEREDOC)
// 			redir->delimiter = tokens->value;
// 		else if (tokens->type == T_WORD)
// 			redir->file = tokens->value;
// 		tokens = tokens->next;
// 		redir = redir->next;
// 	}

// }
t_redirect	*init_redirect(t_redirect *redir)
{
	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->type = NULL;
	redir->file = NULL;
	redir->delimiter = NULL;
	redir->should_be_expand = false;
	redir->next = NULL;
	return (redir);
}

t_cmd	*create_cmd(t_token **token, t_redirect *redirect)
{
	t_cmd	*new_cmd;	//oluşturulucak yeni cmd malloc'a gerek var
	int		i;

	i = 0;
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd) //?sorun çıkması halinde free yapıyor muyuz
		return (NULL);
	while (*token) //? Word olduğu durumu sadece ele alıyorum
	{
		if ((*token)->type == T_WORD)
			new_cmd->argv[i++] = (*token)->value;
		else if (is_redirect((*token)->type) && (*token)->next)
			
		*token = (*token)->next; //sıradaki token'a geç
	}
	
	new_cmd->next = NULL;
	return (new_cmd);
}

void	add_cmd(t_cmd **cmd, t_cmd *new_cmd)
{
	t_cmd	*last_cmd;

	if (!*cmd)
	{
		*cmd = new_cmd;
		return ;
	}
	last_cmd = *cmd;
	while (last_cmd->next)
		last_cmd = last_cmd->next;
	last_cmd->next = new_cmd;
}

void	free_cmdlist(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->redirects)
			free(cmds->redirects);
		cmds = tmp;
	}
}
