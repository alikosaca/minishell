/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 07:54:15 by akosaca           #+#    #+#             */
/*   Updated: 2025/07/01 12:52:06 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void token_command(t_cmd **cmd, t_token *tokens)
{
	t_token	*val;

	val = tokens;
	while (val)
	{
		if (val->type == T_WORD)
			cmd_word(cmd, &tokens);
		val = val->next;
	}
	
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmd;

	cmd = NULL;
	token_command(&cmd, tokens);

	return (cmd);
}
