/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:36:47 by akosaca           #+#    #+#             */
/*   Updated: 2025/06/09 13:16:49 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int skip_whitespace(char **input)
{
	while (**input && is_whitespace(**input))
		(*input)++;
	if (*input)
		return (0);
	else
		return (1);
}
