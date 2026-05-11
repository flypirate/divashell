/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:25:03 by quill             #+#    #+#             */
/*   Updated: 2026/04/22 18:00:29 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

void	redir_append(char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open outfile");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_out(char *out_file)
{
	int	fd;

	fd = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open outfile");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_in(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		perror("open infile");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redir_heredoc(int fd)
{
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redirections(t_cmd *cmd)
{
	t_redir	*current_redir;

	current_redir = cmd->redir;
	while (current_redir)
	{
		if (current_redir->redir_type == INFILE)
			redir_in(current_redir->file);
		else if (current_redir->redir_type == HEREDOC)
			redir_heredoc(current_redir->heredoc_fd);
		else if (current_redir->redir_type == TRUNC)
			redir_out(current_redir->file);
		else if (current_redir->redir_type == APPEND)
			redir_append(current_redir->file);
		current_redir = current_redir->next;
	}
}
