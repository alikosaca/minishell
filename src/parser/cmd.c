/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:15:55 by akosaca           #+#    #+#             */
/*   Updated: 2025/06/28 13:57:45 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_cmd	*create_cmd(char *value, t_redirect *redirect)
{
	t_cmd	*cmd;
	char	**argv;

	cmd = malloc (sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	argv = ft_split(value, ' ');

	cmd->argv = argv;
	cmd->next = NULL;
	if (redirect)
	{
		cmd->redirects->type = redirect->type;
		cmd->redirects->file = redirect->file;
		cmd->next = NULL;
	}
	else
	{
		cmd->redirects = NULL;
	}
	return (cmd);
}
