/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:44:03 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/01 19:10:19 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "structs.h"
# include "env.h"

t_token	*expansion(t_shell *shell, t_token *tokens);

char	*ft_strjoin_free(char *s1, char *s2);
char	*expand_dollar(t_shell *shell, char *str);
char	*expand_dquote(t_shell *shell, char *str);
char	*get_var_value(t_shell *shell, char *str, int *i);

void	check_merge(t_token **token);

t_token	*create_token(t_token_type type, char *value, bool merge);


#endif
