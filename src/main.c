/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:01:35 by yaycicek          #+#    #+#             */
/*   Updated: 2025/07/10 17:27:07 by akosaca          ###   ########.fr       */
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

static int	is_redirection_file(t_token *tokens, t_token *current)
{
    t_token *tmp = tokens;
    
    // Bu token'dan önceki token'ı bul
    while (tmp && tmp->next != current)
        tmp = tmp->next;
    
    // Önceki token redirection mu?
    if (tmp && tmp->type >= T_REDIRECT_IN && tmp->type <= T_HEREDOC)
        return (1);
    return (0);
}

static char	**tokens_to_argv(t_token *tokens)
{
    int		i;
    char	**argv;
    t_token	*tmp;

    // Önce sadece komut argümanlarını say
    i = 0;
    tmp = tokens;
    while (tmp)
    {
        if (tmp->type == T_WORD && !is_redirection_file(tokens, tmp))
            i++;
        tmp = tmp->next;
    }
    
    argv = malloc(sizeof(char *) * (i + 1));
    if (!argv)
        return (NULL);
    
    // Şimdi sadece komut argümanlarını ekle
    tmp = tokens;
    i = 0;
    while (tmp)
    {
        if (tmp->type == T_WORD && !is_redirection_file(tokens, tmp))
            argv[i++] = tmp->value;
        tmp = tmp->next;
    }
    argv[i] = NULL;
    return (argv);
}

static t_redirect_type	token_to_redirect_type(t_token_type type)
{
	if (type == T_REDIRECT_IN)
		return (REDIR_IN);
	else if (type == T_REDIRECT_OUT)
		return (REDIR_OUT);
	else if (type == T_REDIRECT_APPEND)
		return (REDIR_APPEND);
	else if (type == T_HEREDOC)
		return (REDIR_HEREDOC);
	return (REDIR_IN); // varsayılan dönüş
}

static t_redirect	*parse_redirects(t_token *tokens)
{
	t_redirect	*head = NULL;
	t_redirect	*last = NULL;
	t_redirect	*new;

	while (tokens && tokens->next)
	{
		if (tokens->type >= T_REDIRECT_IN && tokens->type <= T_HEREDOC)
		{
			new = malloc(sizeof(t_redirect));
			if (!new)
				return (NULL);
			new->type = token_to_redirect_type(tokens->type);
			new->file = NULL;
			new->delimiter = NULL;
			new->should_be_expand = false;
			new->next = NULL;

			if (tokens->type == T_HEREDOC)
			{
				new->delimiter = tokens->next->value;
				if (tokens->next->type == T_DOLLAR)
					new->should_be_expand = true;
			}
			else
			{
				new->file = tokens->next->value;
			}
			if (!head)
				head = new;
			else
				last->next = new;
			last = new;
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (head);
}

static t_cmd	*create_cmds(t_token *tokens, t_cmd *cmd)
{
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = tokens_to_argv(tokens);
	cmd->redirects = parse_redirects(tokens);
	cmd->next = NULL;
	return (cmd);
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
	shell->exitcode = executor(shell, shell->commands);
	return ;
}

static void	loop(t_shell *shell)
{
	while (true)
	{
		check_signals();
		shell->input = readline(shell->prompt);
		if (!shell->input)
			builtin_exit(shell, (char *[]){"exit", NULL});
		if ((*shell->input))
			add_history(shell->input);
		// if (g_exit_status == 130)
		// 	shell->exitcode = g_exit_status;
		if (g_exit_status == 130 && shell->input && shell->input[0] == '\0')
    		shell->exitcode = g_exit_status;
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
