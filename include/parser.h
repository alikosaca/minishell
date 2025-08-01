/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:05:52 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/02 00:59:56 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"
# include "lexer.h"

int	argc_len(t_token *token); //* Test


int	add_to_argv(t_cmd **args, char *value);
int	add_to_redirect(t_redirect **redir, t_token **tokens);
int	add_cmd(t_cmd **cmd, t_cmd *new_cmd);

t_redirect	*init_redirect();

int	init_newcmd(t_cmd **new_cmd, t_token *token);

//t_cmd	*init_cmd(t_redirect *redir, char **argv);

void	free_redirlist(t_redirect **redir);
void	free_cmdlist(t_cmd **cmd);


t_cmd	*parser(t_token *tokens);


int	is_redirect(t_token_type type);
int	is_pipe(t_token_type type);

t_redirect_type	redirect_type(t_token_type type);

#endif
