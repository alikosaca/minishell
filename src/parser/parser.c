/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 07:54:15 by akosaca           #+#    #+#             */
/*   Updated: 2025/07/04 18:42:04 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void process_command(t_cmd **cmd, t_token *tokens)
{
	t_token	*val;
	t_cmd	*new_cmd;

	//cmd = malloc(sizeof(t_cmd));
	val = tokens;
	while (val)
	{
		new_cmd = init_cmd(&new_cmd);
		if (val->type == T_WORD)
			add_to_argv(new_cmd, &tokens);
		else if (val->type == is_redirect(val->type))
			if (val->next)
				add_to_redirect(new_cmd, &tokens);
		val = val->next;
		add_cmd(cmd, new_cmd);
		
	}
	
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmd;

	cmd = NULL;
	token_command(&cmd, tokens);

	return (cmd);
}
