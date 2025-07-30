/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:48:41 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/30 16:37:59 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signal.h"

static t_shell			*g_shell_ptr;
volatile sig_atomic_t	g_sig = 0;

static void	set_shell_ptr(t_shell *shell)
{
    g_shell_ptr = shell;
}

void	sigint_handler(int sig)	
{
	(void)sig;
	g_sig = 130;
	g_shell_ptr->exitcode = g_sig;
	g_sig = 0;
	printf("\n");
	if (g_shell_ptr->heredoc == false)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_signals(t_shell *shell)
{
    set_shell_ptr(shell);
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}
