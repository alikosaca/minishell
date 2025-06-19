/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:05:52 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/19 16:04:06 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef enum e_redirect_type
{
	REDIR_INPUT,        // <
	REDIR_OUTPUT,       // >
	REDIR_APPEND,       // >>
	REDIR_HEREDOC       // <<
}	t_redirect_type;

typedef struct s_redirect
{
	t_redirect_type		type;         // redirection tipi
	char				*file;        // hedef dosya adı
	char				*limiter;     // heredoc limiter
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command
{
	char				**argv;       // execve için argüman listesi (with NULL terminated)
	t_redirect			*redirects;   // redirection listesi (last arg: NULL)
	struct s_command	*next;        // pipe varsa bir sonraki komuta
}	t_command;

#endif
