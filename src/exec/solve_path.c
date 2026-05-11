/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:56:02 by quill             #+#    #+#             */
/*   Updated: 2026/04/22 22:23:28 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

char	*get_path_line(char **envp)
{
	int		i;
	char	*path_line;

	i = 0;
	path_line = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_line = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (path_line);
}

char	*build_command(char *cmd, char *path)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	if (!full_path)
		return (NULL);
	return (full_path);
}

char	*find_path(char *cmd, char *path_line)
{
	char	**paths;
	char	*full_path;
	int		i;

	i = 0;
	paths = ft_split(path_line, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full_path = build_command(cmd, paths[i]);
		if (!full_path)
		{
			free_matrix(paths);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
			return (free_matrix(paths), full_path);
		free(full_path);
		i++;
	}
	free_matrix(paths);
	return (NULL);
}

char	*resolve_path(char *cmd, char **envp)
{
	char	*path_line;
	char	*path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_line = get_path_line(envp);
	if (path_line == NULL)
		return (NULL);
	path = find_path(cmd, path_line);
	if (path == NULL)
		return (NULL);
	return (path);
}
