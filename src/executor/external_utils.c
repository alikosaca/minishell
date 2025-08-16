/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:23:48 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/16 09:45:27 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

static char	*find_full_path(char **paths, char *cmd)
{
	int		i;
	char	*path;
	char	*temp;

	if (!paths || !paths[0])
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd);
		_free((void **)&temp);
		if (access(path, X_OK) == 0)
		{
			__free((void ***)&paths);
			return (path);
		}
		_free((void **)&path);
		i++;
	}
	__free((void ***)&paths);
	return (NULL);
}

char	*find_cmd_path(t_shell *shell, char *cmd)
{
	char	*path;
	char	**paths;

	path = NULL;
	paths = NULL;
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = get_env_value(shell->envlist, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	path = find_full_path(paths, cmd);
	if (!path)
		return (NULL);
	return (path);
}

static void	clean_and_exit(t_shell *shell, t_cmd *cmd, char *msg, int exc)
{
	cmd_err(shell, cmd->argv[0], msg, exc);
	cleanup(shell);
	exit(shell->exitcode);
}

void	validate_cmd_path(t_shell *shell, t_cmd *cmd, char *path)
{
	struct stat	st;

	if (!path || (path && !ft_strcmp(cmd->argv[0], "..")))
	{
		_free((void **)&path);
		clean_and_exit(shell, cmd, ERR_CMD_NOT_FOUND, 127);
	}
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		_free((void **)&path);
		clean_and_exit(shell, cmd, ERR_IS_A_DIR, 126);
	}
	if (access(path, F_OK) != 0)
	{
		_free((void **)&path);
		clean_and_exit(shell, cmd, strerror(errno), 127);
	}
	if (access(path, X_OK) != 0)
	{
		_free((void **)&path);
		clean_and_exit(shell, cmd, strerror(errno), 126);
	}
}
