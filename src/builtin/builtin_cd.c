/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:15:49 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/18 03:11:12 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static int	find_home_dir(t_env *envlist)
{
	char	*home;

	home = get_env_value(envlist, "HOME");
	if (!home)
		return (error("cd", NULL, ERR_HOME_NOT_SET, 1));
	if (chdir(home) == -1)
		return (error("cd", home, strerror(errno), 1));
	return (0);
}

static int	find_path(char *path)
{
	if (chdir(path) == -1)
		return (error("cd", path, strerror(errno), 1));
	return (0);
}

int	builtin_cd(t_env *envlist, char **args)
{
	if (!args[1])
		return (find_home_dir(envlist));
	else if (args[1] && args[2])
		return (error("cd", NULL, ERR_TOO_MANY_ARGS, 1));
	else
		return (find_path(args[1]));
	return (0);
}
