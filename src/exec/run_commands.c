/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 13:56:24 by acarbajo          #+#    #+#             */
/*   Updated: 2026/04/26 22:11:19 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

void	handle_command_not_found(t_cmd *cmd, t_minishell *shell)
{
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("command not found\n", 2);
	shell->last_exit_status = 127;
	return ;
}

void	execute_simple_command(t_minishell *shell)
{
	char	*path;

	if (!shell->cmd || !shell->cmd->args || !shell->cmd->args[0])
		return ;
	if (shell->cmd->args[0][0] == '\0')
		path = NULL;
	else
		path = resolve_path(shell->cmd->args[0], shell->envp);
	if (path == NULL)
	{
		handle_command_not_found(shell->cmd, shell);
		exit(127);
	}
	execve(path, shell->cmd->args, shell->envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	child_process(t_minishell *shell, t_cmd *cmd, t_pipex *pipex)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	shell->cmd = cmd;
	if (pipex->prev_fd != -1)
		handle_dup_prev_fd(pipex);
	if (cmd->pipe_next)
		handle_dup_pipe_next(pipex);
	redirections(cmd);
	if (!cmd->args[0])
	{
		restore_fd(shell);
		exit(shell->last_exit_status);
	}
	if (is_builtin(cmd->args[0]))
	{
		execute_builtin(shell);
		exit(shell->last_exit_status);
	}
	execute_simple_command(shell);
}

int	handle_command(t_minishell *shell, t_cmd *cmd)
{
	if (cmd->pipe_next)
	{
		if (pipe(shell->pipex->pipe_fd) == -1)
		{
			perror("pipe");
			return (0);
		}
	}
	shell->pipex->pid = fork();
	if (shell->pipex->pid == -1)
	{
		perror("fork");
		return (0);
	}
	if (shell->pipex->pid == 0)
		child_process(shell, cmd, shell->pipex);
	parent_process(shell->pipex, cmd->redir, shell);
	shell->pipex->last_pid = shell->pipex->pid;
	return (1);
}

void	run_commands(t_minishell *shell)
{
	t_cmd	*current_cmd;

	current_cmd = shell->cmd;
	save_original_fd(shell);
	if (current_cmd && current_cmd->args && current_cmd->args[0])
	{
		if (!current_cmd->pipe_next && is_builtin(current_cmd->args[0]))
		{
			redirections(current_cmd);
			execute_builtin(shell);
			restore_fd(shell);
			current_cmd = NULL;
		}
	}
	while (current_cmd)
	{
		if (!handle_command(shell, current_cmd))
		{
			restore_fd(shell);
			return ;
		}
		restore_fd(shell);
		current_cmd = current_cmd->pipe_next;
	}
	restore_fd(shell);
}
