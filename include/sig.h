/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:09:40 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/22 17:12:09 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>

# include "libft.h"
# include "structs.h"

# define MSG_SIGQUIT "Quit (core dumped)"

extern volatile sig_atomic_t	g_sig;

void	interactive_signals(void);
void	heredoc_signals(void);
void	sig_dfl(void);

#endif
