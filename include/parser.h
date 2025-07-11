/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:05:52 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/11 16:58:13 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"
# include "lexer.h"

int	argc_len(t_token *token); //* Test


int	add_to_argv(t_arglist **args, char *value);
int	add_to_redirect(t_redirect **redirects, t_redirect **head, t_token **tokens);
int	add_cmd(t_cmd **cmd, t_redirect *redir, char **argv);

t_redirect	*init_redirect();
// char	**init_argvlist(t_arglist **args);
int	init_argvlist(t_arglist **args, t_token *token);

t_cmd	*init_cmd(t_redirect *redir, char **argv);

void	free_redirlist(t_redirect *redir);
void	free_cmdlist(t_cmd *cmd);


t_cmd	*parser(t_token *tokens);


int	is_redirect(t_token_type type);
int	is_pipe(t_token_type type);

t_redirect_type	redirect_type(t_token_type type);

#endif
