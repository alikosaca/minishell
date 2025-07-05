/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:15:49 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/05 12:13:40 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static int	update_pwd_vars(t_shell *shell)
{
	char	newpwd[PATH_MAX];
	t_env	*pwd;

	if (!getcwd(newpwd, sizeof(newpwd)))
		return (cmd_err(shell, "cd", strerror(errno), 1)); // check!
	pwd = find_env(shell->envlist, "PWD");
	if (pwd)
		add_env(&(shell->envlist), "OLDPWD", pwd->value, true);
	add_env(&(shell->envlist), "PWD", newpwd, true);
	return (0);
}

static int	find_home_dir(t_shell *shell)
{
	char	*home;

	home = get_env_value(shell->envlist, "HOME");
	if (!home)
		return (cmd_err(shell, "cd", ERR_HOME_NOT_SET, 1));
	if (chdir(home) == -1)
		return (cmd_err(shell, "cd", strerror(errno), 1));
	return (update_pwd_vars(shell));
}

static int	find_path(t_shell *shell, char *path)
{
	if (chdir(path) == -1)
		return (cmd_err(shell, "cd", strerror(errno), 1));
	return (update_pwd_vars(shell));
}

int	builtin_cd(t_shell *shell, char **argv)
{
	if (!argv[1])
		return (find_home_dir(shell));
	else if (argv[1] && argv[2])
		return (cmd_err(shell, "cd", ERR_TOO_MANY_ARGS, 1));
	else
	{
		shell->exitcode = find_path(shell, argv[1]);
		return (shell->exitcode);
	}
	return (shell->exitcode);
}
