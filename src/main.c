/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:01:35 by yaycicek          #+#    #+#             */
/*   Updated: 2025/06/29 13:25:54 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

const char *get_token_type_str(t_token_type type)
{
	switch (type)
	{
		case T_WORD:			return "T_WORD";
		case T_PIPE:			return "T_PIPE";
		case T_REDIRECT_IN:		return "T_REDIRECT_IN";
		case T_REDIRECT_OUT:	return "T_REDIRECT_OUT";
		case T_REDIRECT_APPEND:	return "T_REDIRECT_APPEND";
		case T_HEREDOC:			return "T_HEREDOC";
		case T_SINGLE_QUOTE:	return "T_SINGLE_QUOTE";
		case T_DOUBLE_QUOTE:	return "T_DOUBLE_QUOTE";
		case T_DOLLAR:			return "T_DOLLAR";
		case T_ERROR:			return "T_ERROR";
		default:				return "UNKNOWN";
	}
}

void	print_tokens(t_token *token_list)
{
	int i = 1;
	while (token_list)
	{
		printf("Token %d:\n", i++);
		printf("	Type : %s\n", get_token_type_str(token_list->type));
		printf("	Value: %s\n\n", token_list->value);
		token_list = token_list->next;
	}
}


static void	process_input(t_shell *shell)
{
	shell->tokens = lexer(shell->input);
	if (!shell->tokens)
		return ;
	print_tokens(shell->tokens);
	shell->tokens = expansion(shell, shell->tokens);
	if (!shell->tokens)
		return ;
	printf("-----------------------\n");
	print_tokens(shell->tokens);
	return ;
}

static void	loop(t_shell *shell)
{
	while (1)
	{
		check_signals();
		shell->input = readline(shell->prompt);
		if (!shell->input)
		{
			printf("exit\n");
			break;
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
