/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 21:45:25 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/09 15:04:32 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_redirect	*get_last_redir(t_redirect *redir)
{
	t_redirect	*last;

	last = NULL;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
			last = redir;
		redir = redir->next;
	}
	return (last);
}
