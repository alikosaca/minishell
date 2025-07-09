/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:02:23 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/08 17:04:47 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signal.h"

void	check_signals(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}

void	heredoc_signals(void)
{
    signal(SIGINT, handle_sigint_heredoc);
    signal(SIGQUIT, SIG_IGN);
}

void	ignore_signals(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

void	default_signals(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}
