/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:08:24 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/18 07:55:12 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>

# define BASH_TAG "bash: "

int	error(const char *cmd, const char *target, const char *errmsg, int retval);
int	error_syntax(const char *errmsg, const char *target, int retval);

#endif
