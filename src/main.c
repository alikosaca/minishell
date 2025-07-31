/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:01:35 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/31 13:57:53 by akosaca          ###   ########.fr       */
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
		free(shell->input);
		shell->input = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_shell	*const	shell = &(t_shell){0};

	init_shell(shell, envp);
	loop(shell);
	cleanup(shell);
	rl_clear_history();
	return (shell->exitcode);
}
