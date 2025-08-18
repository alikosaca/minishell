/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaycicek <yaycicek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:42:55 by yaycicek          #+#    #+#             */
/*   Updated: 2025/08/18 21:29:52 by yaycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	handle_input_redir(t_shell *shell, t_redirect *redir)
{
	return (redir_in(shell, redir));
}

static int	handle_heredoc_redir(t_shell *shell, t_redirect *redir,
							t_redirect *last_input)
{
	if (redir == last_input)
	{
		if (dup2(redir->hdoc_fd, STDIN_FILENO) == -1)
		{
			close(redir->hdoc_fd);
			return (cmd_err(shell, "dup2", strerror(errno), 1));
		}
		close(redir->hdoc_fd);
		redir->hdoc_fd = -1;
	}
	return (0);
}

static int	handle_output_redir(t_shell *shell, t_redirect *redir)
{
	if (redir->type == REDIR_OUT)
		return (redir_out(shell, redir));
	else if (redir->type == REDIR_APPEND)
		return (redir_append(shell, redir));
	return (0);
}

static int	process_single_redirect(t_shell *shell, t_redirect *redir,
								t_redirect *last_input)
{
	if (redir->type == REDIR_IN)
		return (handle_input_redir(shell, redir));
	else if (redir->type == REDIR_HEREDOC)
		return (handle_heredoc_redir(shell, redir, last_input));
	else if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		return (handle_output_redir(shell, redir));
	return (0);
}

int	setup_redir(t_shell *shell, t_cmd *cmd)
{
	t_redirect	*redir;
	t_redirect	*last_input;

	if (!cmd || !cmd->redirects)
		return (0);
	last_input = get_last_input_redir(cmd->redirects);
	redir = cmd->redirects;
	while (redir && shell->exitcode == 0)
	{
		shell->exitcode = process_single_redirect(shell, redir, last_input);
		if (shell->exitcode == 130)
			return (shell->exitcode);
		redir = redir->next;
	}
	return (shell->exitcode);
}
