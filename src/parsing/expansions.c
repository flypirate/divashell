/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:38:15 by albegar2          #+#    #+#             */
/*   Updated: 2026/05/11 21:20:39 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

char	*expand_var(char *arg, t_parsedata *data)
{
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buffer = malloc(sizeof(char) * (ft_strlen(arg) + 1));
	if (!buffer)
		return (NULL);
	while (arg[i])
	{
		while (arg[i] && arg[i] != '$')
			buffer[j++] = arg[i++];
		if (arg[i] == '$')
		{
			data->expandarg = arg;
			i++;
			if (!expand_tool(&j, &i, data, &buffer))
				return (free(buffer), NULL);
		}
	}
	return (buffer[j] = '\0', buffer);
}

int	expand_tool(int *j, int *i, t_parsedata *data, char **buffer)
{
	char	*exp;
	char	*tmp;
	int		q;
	int		newj;

	q = 0;
	newj = *j;
	exp = set_expvar(data->expandarg, i, data);
	if (!exp)
	{
		(*buffer)[newj++] = '$';
		*j = newj;
		return (1);
	}
	tmp = ft_realloc(*buffer, sizeof(char) * (*j + ft_strlen(exp) + 2), *j);
	if (!tmp)
		return (free(exp), 0);
	*buffer = tmp;
	while (exp[q])
		(*buffer)[newj++] = exp[q++];
	*j = newj;
	free(exp);
	return (1);
}

char	*set_expvar(char *arg, int *i, t_parsedata *data)
{
	int		k;
	int		q;
	int		len;
	char	*exp;

	k = 0;
	len = *i;
	while (arg[*i] && (ft_isalnum(arg[*i]) || arg[*i] == '_' || arg[*i] == '?'))
		(*i)++;
	len = *i - len;
	if (len == 1 && arg[*i - 1] == '?')
		return (exp = get_exitstatus(data->shell));
	if (len == 0)
		return (NULL);
	exp = malloc(sizeof(char) * (len + 1));
	if (!exp)
		return (NULL);
	q = *i - len;
	while (k < len)
		exp[k++] = arg[q++];
	exp[k] = '\0';
	exp = find_var(data, exp);
	return (exp);
}

char	*get_exitstatus(t_minishell *shell)
{
	char	*exp;

	exp = ft_itoa(shell->last_exit_status);
	return (exp);
}

char	*find_var(t_parsedata *data, char *exp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(exp);
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], exp, len) == 0
			&& data->envp[i][len] == '=')
		{
			free(exp);
			exp = ft_strdup(&data->envp[i][len + 1]);
			break ;
		}
		i++;
	}
	if (!data->envp[i])
	{
		if (exp)
			free(exp);
		return (ft_strdup(""));
	}
	return (exp);
}
