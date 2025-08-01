/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:38:30 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/02 00:57:02 by yaycicek         ###   ########.fr       */
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
	int		start_pos;

	start_pos = (*i) - 1;
	while (input[(*i)] == '$')
		(*i)++;
	res = malloc(sizeof(char) * ((*i - start_pos) + 1));
	if (!res)
		return (NULL);
	ft_memcpy(res, input+start_pos, (*i - start_pos) + 1);
	res[*i - start_pos] = '\0';

	return (res);
}

char	*handle_dollar(char **input)
{
	int		len;
	char	*start;
	char	*result;
	int		i;
	char	*dolar;

	dolar = NULL;
	i = 0;
	(*input)++;
	if ((!**input))
		return (ft_strdup("$"));
	else if (**input == '$')
		dolar = get_len_dollar(*input, &i);	
	*input += i;
	start = *input;
	len = 1;
	if (**input && !((ft_isalpha(**input) || **input == '_' || **input == '?')))
		return (NULL);
	else if ((!**input))
		return (dolar);
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
	if (dolar != NULL)
	{
		char *temp = ft_strjoin(dolar, result);
		_free(&dolar);
        _free(&result);
        return (temp);
	}
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
