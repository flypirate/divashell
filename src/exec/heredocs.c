/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 18:32:09 by quill             #+#    #+#             */
/*   Updated: 2026/04/23 14:58:42 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

void	heredoc_child(t_redir *heredoc, int fd_0, int fd_1)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(fd_0);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, heredoc->delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd_1, line, ft_strlen(line));
		write(fd_1, "\n", 1);
		free(line);
	}
	close(fd_1);
	exit(0);
}

void	heredoc_parent(t_redir *heredoc, int fd_0, int fd_1)
{
	close(fd_1);
	heredoc->heredoc_fd = fd_0;
}

int	heredoc_signal(int pid, int fd_0, t_minishell *shell)
{
	int	status;

	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(fd_0);
		shell->last_exit_status = 130;
		return (1);
	}
	return (0);
}

int	read_heredoc(t_redir *heredoc, t_minishell *shell)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	if (pid == 0)
		heredoc_child(heredoc, fd[0], fd[1]);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		heredoc_parent(heredoc, fd[0], fd[1]);
		if (heredoc_signal(pid, fd[0], shell) == 1)
			return (1);
	}
	return (0);
}

int	save_heredocs(t_minishell *shell)
{
	t_cmd	*current_cmd;
	t_redir	*current_redir;

	current_cmd = shell->cmd;
	while (current_cmd)
	{
		current_redir = current_cmd->redir;
		while (current_redir)
		{
			if (current_redir->redir_type == HEREDOC)
			{
				if (read_heredoc(current_redir, shell) == 1)
					return (1);
			}
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->pipe_next;
	}
	return (0);
}
