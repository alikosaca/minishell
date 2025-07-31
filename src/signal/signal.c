/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:48:41 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/31 12:40:40 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signal.h"

volatile sig_atomic_t	g_sig = 0;

void	sigint_handler(int sig)	
{
	(void)sig;
	g_sig = 130;
	printf("\n");
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
