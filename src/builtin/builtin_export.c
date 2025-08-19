/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:15:16 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/19 21:49:40 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static t_env	*find_next_min(t_env *envlist, t_env *last)
{
	t_env	*min;

	min = NULL;
	while (envlist)
	{
		if (envlist->key && ft_strcmp(envlist->key, "_") == 0)
		{
			envlist = envlist->next;
			continue ;
		}
		if (envlist->key && envlist->exported
			&& (!last || ft_strcmp(envlist->key, last->key) > 0)
			&& (!min || ft_strcmp(envlist->key, min->key) < 0))
		{
			min = envlist;
		}
		envlist = envlist->next;
	}
	return (min);
}

static int	print_export_list(t_env *envlist)
{
	t_env	*last;
	t_env	*min;

	last = NULL;
	min = find_next_min(envlist, last);
	while (min)
	{
		printf("declare -x %s", min->key);
		if (min->value)
			printf("=\"%s\"", min->value);
		printf("\n");
		last = min;
		min = find_next_min(envlist, last);
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
	while (arg[i] && (!equal_sign || &arg[i] < equal_sign))
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_export(t_shell *shell, char **argv)
{
	int	ret;
	int	i;

	if (!argv[1])
		shell->exitcode = print_export_list(shell->envlist);
	ret = 0;
	i = 1;
	while (argv[i])
	{
		if (is_valid_identifier(argv[i]))
		{
			if (!add_sys_env(&(shell->envlist), argv[i]))
				return (1);
		}
		else
		{
			ret = 1;
			exp_err(shell, argv[i], ERR_NOT_A_VALID_IDENT, ret);
		}
		i++;
	}
	return (ret);
}
