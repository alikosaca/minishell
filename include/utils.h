/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:08:24 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/05 12:10:48 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include "structs.h"
# include "../libft/libft.h"

# define BASH "bash"

# define ERR_SYNTAX "syntax error near unexpected token"

int		cmd_err(t_shell *shell, char *cmd, char *msg, int ret);
int		lx_err(t_shell *shell, char *sep);

#endif
