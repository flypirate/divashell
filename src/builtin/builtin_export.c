/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quill <quill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 21:32:05 by albegar2          #+#    #+#             */
/*   Updated: 2026/04/27 12:53:09 by quill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

static void	swap_strings(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_env(char **sorted)
{
	int		i;
	int		j;
	int		len;

	i = -1;
	len = env_count(sorted);
	while (++i < len - 1)
	{
		j = -1;
		while (++j < len - 1)
		{
			if (ft_strcmp(sorted[j], sorted[j + 1]) > 0)
				swap_strings(&sorted[j], &sorted[j + 1]);
		}
	}
}

int	print_special_export(t_minishell *shell)
{
	char	**env_copy;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	env_copy = copy_env(shell->envp);
	if (!env_copy)
		return (1);
	sort_env(env_copy);
	while (env_copy[i])
	{
		key = env_copy[i];
		value = ft_strchr(env_copy[i], '=');
		if (value)
		{
			*value = '\0';
			value++;
			printf("declare -x %s=\"%s\"\n", key, value);
		}
		else
			printf("declare -x %s\n", key);
		i++;
	}
	return (free_matrix(env_copy), 0);
}

static int	handle_export_arg(char **cmd, t_minishell *shell, int i)
{
	int		j;
	char	*entry;

	if (!valid_identifier(cmd[i]))
		return (export_helper(cmd, shell, i), 0);
	j = find_key_index(shell->envp, cmd[i]);
	if (!ft_strchr(cmd[i], '=') && j >= 0)
		return (0);
	export_entry(&entry, cmd, i);
	if (!entry)
		return (1);
	if (j >= 0)
	{
		free(shell->envp[j]);
		shell->envp[j] = entry;
	}
	else if (append_env(entry, shell) != 0)
		return (free(entry), 1);
	return (0);
}

int	export_builtin(char **cmd, t_minishell *shell)
{
	int	i;

	if (!cmd[1])
		return (print_special_export(shell));
	i = 1;
	shell->last_exit_status = 0;
	while (cmd[i])
	{
		if (handle_export_arg(cmd, shell, i) != 0)
			return (1);
		i++;
	}
	return (0);
}
