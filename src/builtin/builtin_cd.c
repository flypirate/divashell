/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 21:05:51 by quill             #+#    #+#             */
/*   Updated: 2026/04/22 22:35:00 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

static void	print_cd_error(char *arg, char *error_msg)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(error_msg, 2);
}

char	*cd_sort(t_minishell *shell)
{
	char		*path;
	struct stat	st;

	if (!shell->cmd->args[1])
		path = cd_home(shell);
	else if (ft_strcmp(shell->cmd->args[1], "-") == 0)
		path = cd_reverse(shell);
	else if (shell->cmd->args[1][0] == '/')
		path = ft_strdup(shell->cmd->args[1]);
	else
		path = cd_path(shell);
	if (!path)
		return (NULL);
	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			return (path);
		print_cd_error(shell->cmd->args[1], ": Not a directory\n");
		free(path);
		return (NULL);
	}
	print_cd_error(shell->cmd->args[1], ": No such file or directory\n");
	free(path);
	return (NULL);
}

void	update_cd_path(t_minishell *shell, char *old_pwd, char *current_path)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	set_env(shell->envp, "OLDPWD", old_pwd);
	set_env(shell->envp, "PWD", new_pwd);
	free(old_pwd);
	free(new_pwd);
	free(current_path);
	shell->last_exit_status = 0;
}

void	builtin_cd(t_minishell *shell, char **args)
{
	char	*path;
	char	*old_pwd;

	if (args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		shell->last_exit_status = 1;
		return ;
	}
	path = cd_sort(shell);
	if (!path)
	{
		shell->last_exit_status = 1;
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		free(path);
		free(old_pwd);
		shell->last_exit_status = 1;
		return ;
	}
	update_cd_path(shell, old_pwd, path);
	return ;
}
