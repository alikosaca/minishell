/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:15:55 by akosaca           #+#    #+#             */
/*   Updated: 2025/07/01 21:42:46 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	argv_len(t_token *token)
{
	int	i;

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

t_cmd	*create_cmd(t_token *token, t_redirect *redirect)
{
	t_cmd	*new_cmd;
	char	**argv;
	int		len;
	int		i;

	i = 0;
	len = argv_len(token);
	argv = malloc(sizeof(char *) * (len + 1));
	if (!argv)
		return (NULL);
	while (len > i)
	{
		argv[i] = token->value;
		token = token->next;
		i++;
	}
	argv[i] = NULL;
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
	{
		free(argv);
		return (NULL);
	}
	new_cmd->argv = argv;
	new_cmd->next = NULL;
	if (redirect)
	{
		new_cmd->redirects = malloc(sizeof(t_redirect));
		if (new_cmd->redirects)
		{
			new_cmd->redirects->type = redirect->type;
			new_cmd->redirects->file = redirect->file;
			new_cmd->redirects->next = NULL;
			new_cmd->redirects = redirect;
		}
	}
	else
		new_cmd->redirects = NULL;
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
