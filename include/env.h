/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:09:33 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/19 12:13:04 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../libft/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	bool			exported;
	struct s_env	*next;
}	t_env;

// ENV_INIT
t_env	*create_env_node(char *key, char *value, bool exported);
void	add_sys_env(t_env **envlist, char *envstr);
void	init_envlist(t_env **envlist, char **envp);
void	free_envlist(t_env *envlist);

// ENV_UTILS
t_env	*add_env(t_env **envlist, char *key, char *value, bool exported);
void	remove_env(t_env **envlist, char *key);
t_env	*find_env(t_env *envlist, char *key);
char	*get_env_value(t_env *envlist, char *key);

// ENV_CONVERT
int		count_exported_env(t_env *envlist);
char	*create_envstr(char *key, char *value);
char	**env_to_arr(t_env *envlist);
void	free_env_arr(char **env_arr);

// ENV
void	env(t_env *envlist);

#endif
