/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 21:32:05 by albegar2          #+#    #+#             */
/*   Updated: 2026/04/23 21:04:10 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

int	env_count(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

int	key_len(char *arg)
{
	int	len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	return (len);
}

int	find_key_index(char **envp, char *arg)
{
	int	i;
	int	len;

	i = 0;
	len = key_len(arg);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], arg, len) == 0 && (envp[i][len] == '='
			|| envp[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

int	valid_identifier(char *arg)
{
	int	i;

	if (!arg[0] || (!(ft_isalpha(arg[0])) && arg[0] != '_'))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!(ft_isalnum(arg[i])) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	append_env(char *entry, t_minishell *shell)
{
	int		count;
	char	**new_env;
	int		i;

	count = env_count(shell->envp);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (1);
	i = 0;
	while (i < count)
	{
		new_env[i] = shell->envp[i];
		i++;
	}
	new_env[count] = entry;
	new_env[count + 1] = NULL;
	free(shell->envp);
	shell->envp = new_env;
	return (0);
}
