/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:36:47 by akosaca           #+#    #+#             */
/*   Updated: 2025/06/04 19:18:56 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

int skip_whitespace(char **input)
{
	while (**input && is_whitespace(**input))
		(*input)++;
	if (*input)
		return (0);
	else
		return (1);
}
