/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 00:28:52 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/16 21:09:55 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	_free(void **ptr)
{
	if (!ptr || !(*ptr))
		return ;
	free((*ptr));
	(*ptr) = NULL;
}

void	__free(void ***ptr)
{
	int	i;

	if (!ptr || !(*ptr))
		return ;
	i = 0;
	while ((*ptr)[i])
	{
		_free((void **)&(*ptr)[i]);
		i++;
	}
	free((*ptr));
	(*ptr) = NULL;
}
