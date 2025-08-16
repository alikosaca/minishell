/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 07:54:29 by akosaca           #+#    #+#             */
/*   Updated: 2025/08/16 21:08:36 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_redirect(t_token_type type)
{
	if (type == T_REDIRECT_IN || type == T_REDIRECT_OUT
		|| type == T_REDIRECT_APPEND || type == T_HEREDOC)
		return (1);
	else
		return (0);
}

int	is_pipe(t_token_type type)
{
	if (type == T_PIPE)
		return (1);
	else
		return (0);
}

t_redirect_type	redirect_type(t_token_type type)
{
	t_redirect_type	redirect_type;

	redirect_type = 0;
	if (type == T_REDIRECT_IN)
		redirect_type = REDIR_IN;
	else if (type == T_REDIRECT_OUT)
		redirect_type = REDIR_OUT;
	else if (type == T_REDIRECT_APPEND)
		redirect_type = REDIR_APPEND;
	else if (type == T_HEREDOC)
		redirect_type = REDIR_HEREDOC;
	return (redirect_type);
}
