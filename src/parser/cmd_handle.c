/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:05:12 by akosaca           #+#    #+#             */
/*   Updated: 2025/06/28 14:15:53 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	cmd_word(t_cmd **cmd, t_token **token)
{
	(void)cmd;
	t_token			*next_word;
	t_redirect		*redirect;
	t_token_type	next_token_t;

	next_word = (*token)->next->next;
	next_token_t = (*token)->next->type;
	if (next_token_t && is_redirect(next_token_t))
	{
		redirect->type = redirect_type(next_token_t);
		redirect->file = next_word->value;
		create_cmd((*token)->value, redirect);
	}
	else if (is_pipe(next_token_t))
	{
		//...
	}

}
