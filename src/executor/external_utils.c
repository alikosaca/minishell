/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:23:48 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/07 20:34:02 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

static void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);	
		i++;
	}
	free(arr);
}

static char	*find_path(char **paths, char *cmd)
{
	int	i;
	char	*path;
	char	*temp;

	if (!paths || !paths[0])
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, X_OK) == 0)
		{
			free_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

char	*find_cmd_path(t_shell *shell, char *cmd)
{
	char	**paths;
	char	*path;
	char	*fpath;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = get_env_value(shell->envlist, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	fpath = find_path(paths, cmd);
	if (!fpath)
		return (NULL);
	return (fpath);
}
