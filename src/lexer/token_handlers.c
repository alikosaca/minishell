/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:38:30 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/04 14:47:25 by akosaca          ###   ########.fr       */
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

static char	*get_len_dollar(char *input, int *i)
{
	char	*res;

	(*i)++;
	if (input[(*i)] != '$')
		return (ft_strdup("$"));
	while (input[(*i)] == '$')
		(*i)++;
	res = malloc(sizeof(char) * (*i));
	if (!res)
		return (NULL);
	ft_memcpy(res, input, (*i));
	res[*i] = '\0';
	return (res);
}

static char	*handle_dollar(char **input)
{
	char	*result;
	char	*start;
	int		len;

	start = *input;
	len = 1;
	(*input)++;
	len++;
	while (**input && (ft_isalnum(**input) || **input == '_'))
	{
		(*input)++;
		len++;
	}
	if (!(**input && (ft_isalnum(**input) || **input == '_')))
		len--;
	result = ft_substr(start, 0, len);
	if (!result)
		return (NULL);
	return (result);
}

char	*process_dollar(char **input)
{
	char	*result;
	char	*dollar;
	char	*temp;
	int		i;

	result = NULL;
	dollar = NULL;
	i = 0;
	dollar = get_len_dollar(*input, &i);
	if (!dollar)
		return (NULL);
	*input += i;
	if ((**input && !((ft_isalpha(**input) || \
		**input == '_' || **input == '?'))) || (!**input))
		return (dollar);
	result = handle_dollar(input);
	if (!result)
		return (NULL);
	if (dollar)
	{
		temp = ft_strjoin_free_both(dollar, result);
		return (temp);
	}
	return (result);
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
