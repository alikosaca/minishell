/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:15:16 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/02 12:52:28 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

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

int	builtin_export(t_shell *shell, char **argv)
{
	int	i;

	if (!argv[1])
		shell->exitcode = print_export_list(shell->envlist);
	i = 1;
	while (argv[i])
	{
		if (is_valid_identifier(argv[i]))
		{
			shell->exitcode = 0;
			if (!add_sys_env(&(shell->envlist), argv[i]))
				return (1);
		}
		else
			return (cmd_err(shell, "export", ERR_NOT_A_VALID_IDENT, 1));
		i++;
	}
	return (0);
}
