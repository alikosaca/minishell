/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:44:03 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/09 17:44:27 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "structs.h"
# include "env.h"

t_token	*expansion(t_shell *shell, t_token *tokens);

char	*ft_strjoin_free_first(char *s1, char *s2);
char	*ft_strjoin_free_both(char *s1, char *s2);
char	*expand_dollar(t_shell *shell, char *str, int *i);
bool	check_expand_condition(char *str, int *i, bool is_word);

void	check_merge(t_token **token);

t_token	*create_token(t_token_type type, char *value, bool merge);

size_t	ft_strlen_index(const char *s, int i);
char	*ft_strjoin_index(char const *s1, char const *s2, int i);

char	*handle_question_mark(t_shell *shell, char *fp, int *i, int count);
char	*parse_dollar(t_shell *shell, char *str, int *i);

#endif
