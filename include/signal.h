/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:09:40 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/28 19:18:22 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>

# include "structs.h"

extern volatile sig_atomic_t	g_sig;

void	setup_signals(t_shell *shell);

#endif
