/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 19:25:16 by quill             #+#    #+#             */
/*   Updated: 2026/04/22 22:33:05 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp("echo", cmd) == 0)
		return (1);
	if (ft_strcmp("cd", cmd) == 0)
		return (1);
	if (ft_strcmp("pwd", cmd) == 0)
		return (1);
	if (ft_strcmp("unset", cmd) == 0)
		return (1);
	if (ft_strcmp("export", cmd) == 0)
		return (1);
	if (ft_strcmp("env", cmd) == 0)
		return (1);
	if (ft_strcmp("exit", cmd) == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_minishell *shell)
{
	if (ft_strcmp(shell->cmd->args[0], "echo") == 0)
		builtin_echo(shell->cmd->args, shell);
	else if (ft_strcmp(shell->cmd->args[0], "cd") == 0)
		builtin_cd(shell, shell->cmd->args);
	else if (ft_strcmp(shell->cmd->args[0], "pwd") == 0)
		builtin_pwd(shell->cmd->args, shell);
	else if (ft_strcmp(shell->cmd->args[0], "exit") == 0)
		builtin_exit(shell);
	else if (ft_strcmp(shell->cmd->args[0], "env") == 0)
		env_builtin(shell);
	else if (ft_strcmp(shell->cmd->args[0], "export") == 0)
		export_builtin(shell->cmd->args, shell);
	else if (ft_strcmp(shell->cmd->args[0], "unset") == 0)
		unset_builtin(shell->cmd->args, shell);
}
