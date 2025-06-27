/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:44:03 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/28 00:19:56 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "structs.h"
# include "env.h"

t_token	*expansion(t_shell *shell, t_token *tokens);

char	*expand_dollar(t_shell *shell, char *str);
char	*expand_dquote(t_shell *shell, char *str);

#endif
