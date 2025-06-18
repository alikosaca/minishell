/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:03:04 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/18 07:56:14 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

int	error(const char *cmd, const char *target, const char *errmsg, int retval)
{
	if (target)
		printf(BASH_TAG "%s: %s: %s\n", cmd, target, errmsg);
	else if (cmd)
		printf(BASH_TAG "%s: %s\n", cmd, errmsg);
	else
		printf(BASH_TAG "%s\n", errmsg);
	return (retval);
}

int	error_syntax(const char *errmsg, const char *target, int retval)
{
	if (target)
		printf(BASH_TAG "%s `%s'\n", errmsg, target);
	return (retval);
}
