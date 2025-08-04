/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 00:16:20 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/04 15:41:09 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expansion.h"

char	*ft_strjoin_free_both(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	_free(&s1);
	_free(&s2);
	return (result);
}

char	*ft_strjoin_free_first(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	if (s1)
		_free(&s1);
	return (result);
}

size_t	ft_strlen_index(const char *s, int i)
{
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_index(char const *s1, char const *s2, int i)
{
	char	*join;
	char	*join2;
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen_index(s2, i);
	total_len = s1_len + s2_len;
	join = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!join)
		return (NULL);
	ft_memcpy(join, s1, s1_len);
	join2 = ft_substr(s2, i, s2_len);
	ft_memcpy(join + s1_len, join2, s2_len);
	join[total_len] = '\0';
	return (join);
}