/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 00:28:52 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/02 00:38:50 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

void	_free(char **ptr)
{
	if (!ptr || !(*ptr))
		return ;
	free((*ptr));
	(*ptr) = NULL;	
}

void	__free(char ***ptr)
{
	int	i;

	if (!ptr || !(*ptr))
		return ;
	i = 0;
	while ((*ptr)[i])
	{
		_free(&(*ptr)[i]);
		i++;
	}
	free((*ptr));
	(*ptr) = NULL;
}
