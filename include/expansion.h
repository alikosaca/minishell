/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:44:03 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/18 17:42:28 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "structs.h"
# include "env.h"

t_token	*expansion(t_shell *shell, t_token *tokens);

char	*expand_dollar(t_shell *shell, char *str);
char	*expand_dquote(t_shell *shell, char *str);

void	check_merge(t_token **token);


t_token	*create_token(t_token_type type, char *value, bool merge);
void	add_token(t_token **tokens, t_token *new_token);




#endif
