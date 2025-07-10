/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:01:35 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/10 23:58:53 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// -----------------------------

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


// Main'de commands test etme fonksiyonu
static void	print_commands_debug(t_cmd *commands)
{
    t_cmd		*cmd;
    t_redirect	*redir;
    int			cmd_count;
    int			arg_count;

    if (!commands)
    {
        printf("❌ Commands: NULL\n");
        return ;
    }
    
    cmd = commands;
    cmd_count = 0;
    
    printf("\n🔍 === COMMANDS DEBUG === \n");
    while (cmd)
    {
        printf("📋 Command [%d]:\n", cmd_count);
        
        // Command name - argv[0] kullan
        if (cmd->argv && cmd->argv[0])
            printf("  ├─ cmd: \"%s\"\n", cmd->argv[0]);
        else
            printf("  ├─ cmd: NULL\n");
        
        // Arguments
        if (cmd->argv)
        {
            printf("  ├─ argv: ");
            arg_count = 0;
            while (cmd->argv[arg_count])
            {
                printf("\"%s\"", cmd->argv[arg_count]);
                if (cmd->argv[arg_count + 1])
                    printf(", ");
                arg_count++;
            }
            printf("\n");
            printf("  ├─ argc: %d\n", arg_count);
        }
        else
            printf("  ├─ argv: NULL\n");
        
        // Redirections
        if (cmd->redirects)
        {
            printf("  ├─ redirections:\n");
            redir = cmd->redirects;
            while (redir)
            {
                printf("  │  ├─ type: %d ", redir->type);
                if (redir->type == REDIR_IN)
                    printf("(<)");
                else if (redir->type == REDIR_OUT)
                    printf("(>)");
                else if (redir->type == REDIR_APPEND)
                    printf("(>>)");
                else if (redir->type == REDIR_HEREDOC)
                    printf("(<<)");
                printf("\n");
                
                if (redir->file)
                    printf("  │  ├─ file: \"%s\"\n", redir->file);
                if (redir->delimiter)
                    printf("  │  ├─ delimiter: \"%s\"\n", redir->delimiter);
                
                redir = redir->next;
            }
        }
        else
            printf("  ├─ redirections: NULL\n");
        
        // Next command
        if (cmd->next)
            printf("  └─ has_next: YES\n");
        else
            printf("  └─ has_next: NO\n");
        
        printf("\n");
        cmd = cmd->next;
        cmd_count++;
    }
    printf("🔍 === END DEBUG ===\n\n");
}

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
	print_commands_debug(shell->commands);
	shell->exitcode = executor(shell, shell->commands);
	return ;
}

static void	loop(t_shell *shell)
{
	while (true)
	{
		shell->input = readline(shell->prompt);
		if (!shell->input)
		{
			exit(0);
			break ;
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
