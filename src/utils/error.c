/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:03:04 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/14 10:36:53 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	error(const char *cmd, const char *target, const char *errmsg, int retval)
{
	if (target)
		printf("bash: %s: %s: %s\n", cmd, target, errmsg);
	else if (cmd)
		printf("bash: %s: %s\n", cmd, errmsg);
	else
		printf("bash: %s\n", errmsg);
	return (retval);
}
