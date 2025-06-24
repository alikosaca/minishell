/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:35:34 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/24 15:01:53 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

void	skip_whitespace(char **input)
{
	while (**input && ft_isspace(**input))
		(*input)++;
}

int	check_e_sequence(char *input)
{
	if ((*input == '|' && *(input + 1) == '|')
		|| (*input == '&' && *(input + 1) == '&'))
		return (2);
	if (*input == '&' || *input == '\\' || *input == ';'
		|| *input == '(' || *input == ')')
		return (1);
	return (0);
}
