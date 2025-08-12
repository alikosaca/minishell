/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 00:28:52 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/12 10:16:17 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

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
