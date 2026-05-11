/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 20:09:11 by albegar2          #+#    #+#             */
/*   Updated: 2026/04/26 20:29:18 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

void	export_setvals(char **cmd, t_minishell *shell, int *i, int *j)
{
	if (!valid_identifier(cmd[*i]))
		*i = export_helper(cmd, shell, *i);
	*j = find_key_index(shell->envp, cmd[*i]);
	if (!ft_strchr(cmd[*i], '=') && *j >= 0)
		*i = *i + 1;
}

void	export_entry(char **entry, char **cmd, int i)
{
	if (ft_strchr(cmd[i], '='))
		*entry = ft_strdup(cmd[i]);
	else
		*entry = ft_strjoin(cmd[i], "=");
}

int	export_helper(char **cmd, t_minishell *shell, int i)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(cmd[i], 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	shell->last_exit_status = 1;
	i++;
	return (i);
}
