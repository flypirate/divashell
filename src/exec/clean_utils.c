/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quill <quill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:55:41 by quill             #+#    #+#             */
/*   Updated: 2026/04/27 00:25:32 by quill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_exec(t_minishell *shell)
{
	if (shell->cmd)
		free_cmd(shell->cmd);
	if (shell->pipex)
		free_pipex(shell->pipex);
}

void	free_redir(t_redir *redir)
{
	t_redir	*temp;

	while (redir)
	{
		if (redir->delimiter)
			free(redir->delimiter);
		if (redir->file)
			free(redir->file);
		if (redir->next)
		{
			temp = redir->next;
			free (redir);
			redir = temp;
			temp = NULL;
		}
		else
		{
			free(redir);
			redir = NULL;
		}
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*temp;

	while (cmd)
	{
		if (cmd->args)
			free_matrix(cmd->args);
		if (cmd->redir)
			free_redir(cmd->redir);
		if (cmd->pipe_next)
		{
			temp = cmd->pipe_next;
			free (cmd);
			cmd = temp;
			temp = NULL;
		}
		else
		{
			free(cmd);
			cmd = NULL;
		}
	}
}

void	free_pipex(t_pipex *pipex)
{
	if (pipex->pipe_fd[0] != -1)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] != -1)
		close(pipex->pipe_fd[1]);
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	free(pipex);
}
