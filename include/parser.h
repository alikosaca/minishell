/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:05:52 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/04 19:48:13 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"
# include "lexer.h"

t_cmd	*init_cmd(t_cmd **cmd);
char	**add_to_argv(t_cmd *cmd, t_token **tokens);
int		argv_len(t_token *token);
void	*add_to_redirect(t_cmd *cmd, t_token **tokens);
t_redirect	*init_redirect(t_redirect **redirect);



t_cmd	*parser(t_token *tokens);
t_cmd	*create_cmd(char *value, t_redirect *redirect);

void	cmd_word(t_cmd **cmd, t_token *token);
void	add_cmd(t_cmd **cmd, t_cmd *new_cmd);

int	is_pipe(t_token_type type);
int	is_redirect(t_token_type type);

t_redirect_type	redirect_type(t_token_type *type);

#endif


