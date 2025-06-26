/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:05:52 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/25 20:13:57 by yaycicek         ###   ########.fr       */
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
	char				*delimiter;     // heredoc delimiter
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd
{
	char				**argv;       // execve için argüman listesi (with NULL terminated)
	t_redirect			*redirects;   // redirection listesi (last arg: NULL)
	struct s_command	*next;        // pipe varsa bir sonraki komuta
}	t_cmd;

#endif

void	cmd_word(t_cmd **cmd, t_token *token);

