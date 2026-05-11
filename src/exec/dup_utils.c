/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:07:57 by acarbajo          #+#    #+#             */
/*   Updated: 2026/04/23 15:27:52 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

void	handle_dup_prev_fd(t_pipex *pipex)
{
	dup2(pipex->prev_fd, STDIN_FILENO);
	close(pipex->prev_fd);
}

void	handle_dup_pipe_next(t_pipex *pipex)
{
	dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	close(pipex->pipe_fd[1]);
	close(pipex->pipe_fd[0]);
}
