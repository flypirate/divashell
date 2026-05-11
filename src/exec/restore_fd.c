/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:56:44 by quill             #+#    #+#             */
/*   Updated: 2026/04/26 22:11:24 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

void	save_original_fd(t_minishell *shell)
{
	if (shell->original_stdout == -1)
		shell->original_stdout = dup(STDOUT_FILENO);
	if (shell->original_stdin == -1)
		shell->original_stdin = dup(STDIN_FILENO);
}

void	restore_fd(t_minishell *shell)
{
	if (shell->original_stdout != -1)
	{
		dup2(shell->original_stdout, STDOUT_FILENO);
		close(shell->original_stdout);
		shell->original_stdout = -1;
	}
	if (shell->original_stdin != -1)
	{
		dup2(shell->original_stdin, STDIN_FILENO);
		close(shell->original_stdin);
		shell->original_stdin = -1;
	}
}
