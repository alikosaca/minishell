/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:09:40 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/16 10:48:47 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>

# include "structs.h"

# define MSG_SIGQUIT "Quit (core dumped)"

extern volatile sig_atomic_t	g_sig;

void	interactive_signals(void);
void	heredoc_signals(void);
void	sig_dfl(void);

#endif
