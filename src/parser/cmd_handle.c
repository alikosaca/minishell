/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:05:12 by akosaca           #+#    #+#             */
/*   Updated: 2025/07/01 21:42:22 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	cmd_word(t_cmd **cmd, t_token **token)
{
	t_token			*next_word;
	t_redirect		*redirect;
	t_token_type	next_token_t;

	
	if ((*token)->next && (*token)->next->next)
	{
		next_word = (*token)->next->next;
		next_token_t = (*token)->next->type;
		if (next_token_t && is_redirect(next_token_t))
		{
			redirect->type = redirect_type(next_token_t);
			redirect->file = next_word->value;
			add_cmd(cmd, create_cmd(token, redirect));
		}
	}
	else if (is_pipe(next_token_t))
	{
		//...
	}
	else
	{
		// Eğer ki sadece word gelirse buraya gelecek
		add_cmd(cmd, create_cmd((*token)->value, NULL)); //! Main'de dene
	}
}
