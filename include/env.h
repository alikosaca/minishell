/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:09:33 by yaycicek          #+#    #+#             */
/*   Updated: 2025/05/25 15:31:26 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

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

// ENV
t_env	*create_env_node(char *key, char *value, bool exported);
void	add_sys_env(t_env **env_list, char *env_str);

// ENV_UTILS
t_env	*add_env(t_env **env_list, char *key, char *value, bool *exported);

#endif
