/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 20:37:06 by acarbajo          #+#    #+#             */
/*   Updated: 2026/04/22 20:54:19 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

void	builtin_pwd(char **args, t_minishell *shell)
{
	char	*path;

	if (args[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		shell->last_exit_status = 1;
		return ;
	}
	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("pwd");
		shell->last_exit_status = 1;
		return ;
	}
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	free(path);
	shell->last_exit_status = 0;
	return ;
}
