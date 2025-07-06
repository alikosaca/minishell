/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 07:54:15 by akosaca           #+#    #+#             */
/*   Updated: 2025/07/06 19:22:08 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void process_command(t_cmd **cmd, t_token *tokens)
{
	t_token	*val;
	t_cmd	*new_cmd;
	t_redirect	*redir_tmp;
	t_redirect	*redir_first;
	t_redirect	*redir_last;

	val = tokens;
	while (val)
	{
		new_cmd = init_cmd(&new_cmd);
		while (val && val->type != T_PIPE)
		{
			if (val->type == T_WORD)
				new_cmd->argv = add_to_argv(tokens->value);
			else if (val->type == is_redirect(val->type) && val->next)
			{
				t_redirect	*new_redir = add_to_redirect(tokens);
				if (!redir_tmp)
				{
					redir_tmp = new_redir;
					redir_last = new_redir;
				}
				else
				{
					redir_last->next = new_redir;
					redir_last = redir_last->next;
				}
			}
			val = val->next;
		}
		add_cmd(cmd, new_cmd);
	}	
}
	

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmd;

	cmd = NULL;
	process_command(&cmd, tokens);

	return (cmd);
}
