/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:15:16 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/18 02:50:30 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	print_export_list(t_env *envlist)
{
	while (envlist)
	{
		if (envlist->key && envlist->exported)
		{
			printf("declare -x %s", envlist->key);
			if (envlist->value)
				printf("=\"%s\"", envlist->value);
			printf("\n");
		}
		envlist = envlist->next;
	}
	return (0);
}

static int	is_valid_identifier(char *arg)
{
	int		i;
	char	*equal_sign;

	if (!arg || !(*arg))
		return (0);
	equal_sign = ft_strchr(arg, '=');
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i] && (equal_sign == NULL || &arg[i] < equal_sign))
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_export(t_env **envlist, char **args)
{
	int	i;

	if (!args[1])
		return (print_export_list((*envlist)));
	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]))
			add_sys_env(envlist, args[i]);
		else
			return (error("export", args[i], ERR_NOT_A_VALID_IDENTIFIER, 1));
		i++;
	}
	return (0);
}
