/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 07:54:15 by akosaca           #+#    #+#             */
/*   Updated: 2025/07/11 18:16:39 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	process_command(t_cmd **cmd, t_token *token)
{
	t_redirect	*redir;
	t_redirect	*redir_head;
	int			status;
	t_arglist	*args;

	status = 0;
	args = NULL;
	while (token && !status)
	{
		redir = NULL;
		redir_head = NULL;
		args = malloc(sizeof(t_arglist));
        if (!args)
        {
            status = 1;
            break;
        }
		status = init_argvlist(&args, token);

		while (token && token->type != T_PIPE && !status)
		{
			if (token->type == T_WORD)
			{
				status = add_to_argv(&args, token->value);
			}
			else if (is_redirect(token->type) && token->next)
				status = add_to_redirect(&redir, &redir_head, &token);
			token = token->next;
		}
		if (!status)
			status = add_cmd(cmd, redir_head, args->argv);
		if (token && token->type == T_PIPE)
			token = token->next;
	}
	if (status)
		free_cmdlist((*cmd));
	


		


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
