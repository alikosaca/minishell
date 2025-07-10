/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 07:54:15 by akosaca           #+#    #+#             */
/*   Updated: 2025/07/10 17:18:32 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	process_command(t_cmd **cmd, t_token *token)
{
	t_redirect	*redir;
	t_redirect	*redir_head;
	int			status;
	t_arglist	args  = {0};

	status = 0;
	while (token && !status)
	{
		redir = NULL;
		redir_head = NULL;
		args.argv = NULL;
		args.argc = 0;
		while (token && token->type != T_PIPE && !status)
		{
			if (token->type == T_WORD)
				status = add_to_argv(&args, token->value);
			else if (is_redirect(token->type) && token->next)
				status = add_to_redirect(&redir, &redir_head, &token);
			token = token->next;
		}
		if (!status)
			status = add_cmd(cmd, redir_head, args.argv);
		if (token && token->type == T_PIPE)
			token = token->next;
	}
	if (status)
		free_cmdlist(cmd);
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmd;

	cmd = NULL;
	process_command(&cmd, tokens);
	if (!cmd)
		return (NULL);

	return (cmd);
}
