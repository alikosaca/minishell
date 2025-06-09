/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:15:16 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/09 20:37:54 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	print_export_list(t_env *env_list)
{
	while (env_list)
	{
		if (env_list->exported)
		{
			printf("declare -x %s", env_list->key);
			if (env_list->value)
				printf("=\"%s\"", env_list->value);
			printf("\n");
		}
		env_list = env_list->next;
	}
	return (0);
}

int	builtin_export(t_env **env_list, char **args)
{
	int	i;
	int	ret; // for multiple assignment

	if (!args[1])
		return (print_export_list(*env_list));
	i = 1;
	ret = 0;
}
