/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 21:31:53 by albegar2          #+#    #+#             */
/*   Updated: 2026/04/22 22:33:23 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

void	unsetb_helper(t_minishell *shell, int i)
{
	free(shell->envp[i]);
	while (shell->envp[i + 1])
	{
		shell->envp[i] = shell->envp[i + 1];
		i++;
	}
	shell->envp[i] = NULL;
}

int	unset_builtin(char **cmd, t_minishell *shell)
{
	int	i;
	int	j;
	int	argiter;

	if (!cmd[1])
		return (0);
	argiter = 1;
	while (cmd[argiter])
	{
		i = 0;
		j = ft_strlen(cmd[argiter]);
		while (shell->envp[i])
		{
			if (ft_strncmp(shell->envp[i], cmd[argiter], j) == 0
				&& shell->envp[i][j] == '=')
			{
				unsetb_helper(shell, i);
				break ;
			}
			i++;
		}
		argiter++;
	}
	return (0);
}
