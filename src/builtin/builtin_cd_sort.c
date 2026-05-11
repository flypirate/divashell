/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:28:41 by quill             #+#    #+#             */
/*   Updated: 2026/03/22 02:30:42 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

char	*cd_path(t_minishell *shell)
{
	char	*current_dir;
	char	*temp;
	char	*path;

	current_dir = getcwd(NULL, 0);
	temp = ft_strjoin(current_dir, "/");
	path = ft_strjoin(temp, shell->cmd->args[1]);
	free(current_dir);
	free(temp);
	return (path);
}

char	*cd_reverse(t_minishell *shell)
{
	char	*path;

	path = get_env(shell->envp, "OLDPWD");
	if (!path)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (NULL);
	}
	return (path);
}

char	*cd_home(t_minishell *shell)
{
	char	*path;

	path = get_env(shell->envp, "HOME");
	if (!path)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (NULL);
	}
	return (path);
}
