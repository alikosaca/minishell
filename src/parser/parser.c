/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 07:54:15 by akosaca           #+#    #+#             */
/*   Updated: 2025/07/09 20:58:02 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	process_command(t_cmd **cmd, t_token *token)
{
	t_redirect	*redir;
	t_redirect	*redir_head;
	char		**argv;
	int			*argc;
	int			status;

	redir = NULL;
	argv = NULL;
	argc = 0;
	status = 0;
	while (token && !status)
	{
		while (token && token->type != T_PIPE && !status)
		{
			if (token->type == T_WORD)
				status = add_to_argv(argv, argc, token->value);
			else if (is_redirect(token->type) && token->next)
				status = add_to_redirect(&redir, &redir_head, &token);
			token = token->next;
		}
		status = add_cmd(cmd, redir, argv);
	}
	if (!status)
		free_cmdlist(cmd);
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmd;

	cmd = NULL;
	printf("parser\n ");
	process_command(&cmd, tokens);
	if (!cmd)
		return (NULL);
	return (cmd);
}
