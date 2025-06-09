/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:15:49 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/09 19:53:48 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	find_home_dir(t_env *env_list)
{
	char	*home;

	home = get_env_value(env_list, "HOME");
	if (!home)
		return (error("cd", NULL, ERR_HOME_NOT_SET));
	if (chdir(home) == -1)
		return (error("cd", home, strerror(errno)));
	return (0);
}

static int	find_path(char *path)
{
	if (chdir(path) == -1)
		return (error("cd", path, strerror(errno)));
	return (0);
}

int	builtin_cd(t_env *env_list, char **args)
{
	if (!args[1])
		return (find_home_dir(env_list));
	else if (args[1] && args[2])
		return (error("cd", NULL, ERR_TOO_MANY_ARGS));
	else
		return (find_path(args[1]));
	return (0);
}
