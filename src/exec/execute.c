/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:49:24 by quill             #+#    #+#             */
/*   Updated: 2026/04/23 21:46:52 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

void	parent_process(t_pipex *pipex, t_redir *redir, t_minishell *shell)
{
	t_redir	*current_redir;

	current_redir = redir;
	if (shell->pipex->prev_fd != -1)
		close(shell->pipex->prev_fd);
	pipex->prev_fd = pipex->pipe_fd[0];
	if (pipex->pipe_fd[1] != -1)
		close(pipex->pipe_fd[1]);
	while (current_redir)
	{
		if (current_redir->heredoc_fd > 0)
			close(current_redir->heredoc_fd);
		current_redir = current_redir->next;
	}
}

void	wait_children(t_minishell *shell)
{
	int		status;
	pid_t	pid;

	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == shell->pipex->last_pid)
			update_exit_status(status, shell);
		pid = waitpid(-1, &status, 0);
	}
}

int	init_pipex(t_minishell *shell)
{
	shell->pipex = malloc(sizeof(t_pipex));
	if (!shell->pipex)
	{
		perror("malloc");
		return (0);
	}
	shell->pipex->prev_fd = -1;
	shell->pipex->pipe_fd[0] = -1;
	shell->pipex->pipe_fd[1] = -1;
	return (1);
}

void	execute(t_minishell *shell)
{
	if (!init_pipex(shell))
		return ;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	run_commands(shell);
	wait_children(shell);
	if (g_signal == SIGINT)
	{
		shell->last_exit_status = 130;
		g_signal = 0;
	}
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	if (shell->pipex)
	{
		free(shell->pipex);
		shell->pipex = NULL;
	}
}
