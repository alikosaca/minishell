/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:48:41 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/31 13:49:08 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signal.h"

volatile sig_atomic_t	g_sig = 0;

static void	sigint_handler(int sig)	
{
	(void)sig;
	g_sig = 130;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	sigint_heredoc_handler(int sig)
{
    (void)sig;
    g_sig = 130;
    printf("\n");
}

void	interactive_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_signals(void)
{
    signal(SIGINT, sigint_heredoc_handler);
    signal(SIGQUIT, SIG_IGN);
}
