/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:47:28 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/10 12:38:47 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <string.h>
# include <errno.h>
# include <linux/limits.h>

# include "structs.h"
# include "utils.h"
# include "env.h"

# define ERR_HOME_NOT_SET "HOME not set"
# define ERR_TOO_MANY_ARGS "too many arguments"
# define ERR_NOT_A_VALID_IDENT "not a valid identifier"
# define ERR_NUM_ARG_REQ "numeric argument required"

int		builtin_echo(char **argv);
int		builtin_cd(t_shell *shell, char **argv);
int		builtin_pwd(t_shell *shell);
int		builtin_export(t_shell *shell, char **argv);
int		builtin_unset(t_shell *shell, char **argv);
int		builtin_exit(t_shell *shell, char **argv);

#endif
