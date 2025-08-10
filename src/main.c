/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:01:35 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/10 12:23:03 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	process_input(t_shell *shell)
{
	shell->tokens = lexer(shell, shell->input);
	if (!shell->tokens)
		return ;
	shell->tokens = expansion(shell, shell->tokens);
	if (!shell->tokens)
		return ;
	shell->commands = parser(shell->tokens);
	if (!shell->commands)
		return ;
	shell->exitcode = executor(shell, shell->commands);
	free_tokenlist(&shell->tokens);
	free_cmdlist(&shell->commands);
	return ;
}

static void	loop(t_shell *shell)
{
	interactive_signals();
	while (true)
	{
		shell->input = readline(shell->prompt);
		if (!shell->input)
		{
			printf("exit\n");
			break ;
		}
		if (g_sig == 130)
		{
			shell->exitcode = g_sig;
			g_sig = 0;
		}
		if ((*shell->input))
			add_history(shell->input);
		process_input(shell);
		_free((void **)&shell->input);
	}
}

int	main(void)
{
	extern char		**environ;
	t_shell *const	shell = &(t_shell){0};

	if (init_shell(shell))
		return (1);
	if (!init_envlist(&shell->envlist, environ))
	{
		free_envlist(&shell->envlist);
		return (1);
	}
	loop(shell);
	cleanup(shell);
	clear_history();
	rl_clear_history();
	return (shell->exitcode);
}
