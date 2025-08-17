/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:35:34 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/17 19:47:23 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

int	is_word_delimiter(char c)
{
	return (
		ft_isspace(c)
		|| c == '|'
		|| c == '<'
		|| c == '>'
		|| c == '\''
		|| c == '"'
		|| c == '$'
		|| c == '\0'
		|| check_e_sequence(&c)
	);
}

bool	is_merge(char **input)
{
	if (!ft_strchr("<|> ", **input))
		return (true);
	else
		return (false);
}
