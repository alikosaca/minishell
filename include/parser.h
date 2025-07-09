/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:05:52 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/09 20:11:04 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"
# include "lexer.h"

// int		argv_len(t_token *token);

int	add_to_argv(char **argv, int *argc, char *value);
int	add_to_redirect(t_redirect **redirects, t_redirect **head, t_token **tokens);
int	add_cmd(t_cmd **cmd, t_redirect *redir, char **argv);

t_redirect	*init_redirect();

t_cmd	*init_cmd(t_redirect *redir, char **argv);

void	free_redirlist(t_redirect *redir);
void	free_cmdlist(t_cmd **cmd);


t_cmd	*parser(t_token *tokens);


int	is_redirect(t_token_type type);
int	is_pipe(t_token_type type);

t_redirect_type	redirect_type(t_token_type type);


//cmd_handle.c
// t_cmd	*create_cmd(char *value, t_redirect *redirect);
// void	cmd_word(t_cmd **cmd, t_token *token);








#endif


