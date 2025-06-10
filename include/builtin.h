/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:47:28 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/10 16:40:27 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define ERR_HOME_NOT_SET "HOME not set"
# define ERR_TOO_MANY_ARGS "too many arguments"
# define ERR_NO_SUCH_FILE_OR_DIR "No such file or directory"

# define ERR_NOT_A_VALID_IDENTIFIER "not a valid identifier"

int	builtin_echo(char **args);
int	builtin_cd(t_env *env_list, char **args);
int	builtin_pwd(void);
int	builtin_export(t_env **env_list, char **args);

#endif
