/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 07:54:15 by akosaca           #+#    #+#             */
/*   Updated: 2025/08/09 18:44:00 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	process_command(t_cmd **cmd, t_token *token)
{
	int			status;
	t_cmd		*new_cmd;

	status = 0;
	new_cmd = NULL;
	while (token && !status)
	{
		status = init_newcmd(&new_cmd, token);
		while (token && token->type != T_PIPE && !status)
		{
			if (token->type == T_WORD)
				status = add_to_argv(&new_cmd, token->value);
			else if (is_redirect(token->type) && token->next)
				status = add_to_redirect(&new_cmd->redirects, &token);
			token = token->next;
		}
		if (!status)
			status = add_cmd(cmd, new_cmd);
		if (token && token->type == T_PIPE)
			token = token->next;
	}
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
