/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:15:55 by akosaca           #+#    #+#             */
/*   Updated: 2025/07/04 19:40:59 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	argv_len(t_token **token)
{
	t_token	**tmp;
	int		i;

	tmp = token;
	i = 0;
	if (!token)
		return (0);
	while ((*tmp)->type == T_WORD)
	{
		i++;
		*tmp = (*tmp)->next;
	}
	return (i);
}

char	**add_to_argv(t_cmd *cmd, t_token **tokens)
{
	int	i;

	i = 0;
	cmd->argv = malloc(sizeof(char *) * (argv_len(tokens) + 1));
	if (!cmd->argv)
		return (NULL);
	while ((*tokens)->type == T_WORD)
	{
		cmd->argv[i++] = (*tokens)->value;
		*tokens = (*tokens)->next;
	}
	cmd->argv[i] = NULL;

	return (cmd->argv);
}

t_cmd	*init_cmd(t_cmd **cmd)
{
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	(*cmd)->next = NULL;
	return (cmd);
}


void	*add_to_redirect(t_cmd *cmd, t_token **tokens)
{
	t_redirect	*first_redirect;

	first_redirect = cmd->redirects;
	while ((*tokens)->next->type == T_WORD && is_redirect((*tokens)->value))
	{
		init_redirect(&cmd->redirects);
		cmd->redirects = redirect_type((*tokens)->type);
		*tokens = (*tokens)->next;
		if ((*tokens)->type == T_WORD && cmd->redirects->type == REDIR_HEREDOC)
			cmd->redirects->delimiter = (*tokens)->value;
		else if ((*tokens)->type == T_WORD)
			cmd->redirects->file = (*tokens)->value;
		*tokens = (*tokens)->next;
		cmd->redirects = cmd->redirects->next;
	}

}
t_redirect	*init_redirect(t_redirect **redirect)
{
	redirect = malloc(sizeof(t_redirect));
	if (!redirect)
		return (NULL);
	(*redirect)->next = NULL;
	return (NULL);
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

