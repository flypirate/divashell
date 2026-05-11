/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quill <quill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:25:07 by quill             #+#    #+#             */
/*   Updated: 2026/04/15 19:27:27 by quill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

static int	count_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**copy_env(char **envp)
{
	char	**new_env;
	int		i;
	int		env_count;

	env_count = count_env(envp);
	new_env = ft_calloc(env_count + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < env_count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			free_matrix(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	*get_env(char **envp, char *name)
{
	int	i;
	int	len_name;

	i = 0;
	len_name = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len_name) == 0
			&& envp[i][len_name] == '=')
			return (ft_strdup(&envp[i][len_name + 1]));
		i++;
	}
	return (NULL);
}

void	set_env(char **envp, char *name, char *value)
{
	int		i;
	int		len_name;
	char	*new_value;
	char	*temp;

	i = 0;
	len_name = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len_name) == 0
			&& envp[i][len_name] == '=')
		{
			free(envp[i]);
			temp = ft_strjoin(name, "=");
			new_value = ft_strjoin(temp, value);
			free(temp);
			envp[i] = new_value;
			return ;
		}
		i++;
	}
}
