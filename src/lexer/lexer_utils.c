/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:35:34 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/23 21:05:13 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

void	skip_whitespace(char **input)
{
	while (**input && ft_isspace(**input))
		(*input)++;
}

int	is_error_char(char c)
{
	return (c == '&' || c == '\\' || c == ';' || c == '(' || c == ')');
}

int	check_error_sequence(char *input)
{
	if (*input == '|' && *(input + 1) == '|')
		return (2);
	if (*input == '&' && *(input + 1) == '&')
		return (2);
	return (0);
}
