/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:38:30 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/27 12:36:24 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

char	*handle_quote(char **input)
{
	char	c;
	int		len;
	char	*start;
	char	*result;

	c = (**input);
	(*input)++;
	start = (*input);
	len = 0;
	while ((**input) && (**input) != c)
	{
		(*input)++;
		len++;
	}
	if ((**input) != c)
		return (NULL);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, start, len);
	result[len] = '\0';
	(*input)++;
	return (result);
}

// char	*handle_dollar(char **input)
// {
// 	int		len;
// 	char	*start;
// 	char	*result;

// 	(*input)++;
// 	if (!(**input && (ft_isalpha(**input) || **input == '_' || **input == '?')))
// 		return (NULL);
// 	start = *input;
// 	len = 1;
// 	while (**input && (ft_isalnum(**input) || **input == '_'))
// 	{
// 		(*input)++;
// 		len++;
// 	}
// 	result = malloc(len + 1);
// 	if (!result)
// 		return (NULL);
// 	ft_memcpy(result, start, len);
// 	result[len] = '\0';
// 	return (result);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Updated: 2025/06/27 13:00:00 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*handle_dollar(char **input)
{
    int		len;
    char	*start;
    char	*result;

    start = *input;
    len = 1;
    (*input)++;
    if (!(**input && (ft_isalpha(**input) || **input == '_' || **input == '?')))
        return (NULL);
    else
    {
		(*input)++;
		len++;
        while (**input && (ft_isalnum(**input) || **input == '_'))
        {
            (*input)++;
            len++;
        }
    }
    result = malloc(len + 1);
    if (!result)
        return (NULL);
    ft_memcpy(result, start, len);
    result[len] = '\0';
    return (result);
}

static int	is_word_delimiter(char c)
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

char	*handle_word(char **input)
{
	int		len;
	char	*start;
	char	*result;

	start = *input;
	len = 0;
	while (**input && !is_word_delimiter(**input))
	{
		(*input)++;
		len++;
	}
	if (len == 0)
		return (NULL);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, start, len);
	result[len] = '\0';
	return (result);
}
