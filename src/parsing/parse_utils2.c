/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:59:58 by albegar2          #+#    #+#             */
/*   Updated: 2026/05/11 22:07:30 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

int	ft_isspace(char arg)
{
	if ((arg > 0 && arg <= 13) || arg == 32)
		return (1);
	return (0);
}

void	unexpected(char line, t_parsedata *data)
{
	if (line == '\'' || line == '\"')
	{
		if (line == '\'')
			printf("divashell$: syntax error (unclosed single quote)\n");
		else
			printf("divashell$: syntax error (unclosed double quote)\n");
		data->shell->last_exit_status = 2;
		return ;
	}
	if (line == '>' && data->redirout >= 2)
		printf("divashell$: syntax error near unexpected token '>>'\n");
	else if (line == '<' && data->redirin >= 2)
		printf("divashell$: syntax error near unexpected token '<<'\n");
	else
		printf("divashell$: syntax error near unexpected token '%c'\n", line);
	data->shell->last_exit_status = 2;
}

int	expand_double(char *line, t_parsedata *data, int i)
{
	int		start;
	char	*expanded;
	int		j;

	j = 0;
	start = data->bufpos;
	while (line[i] && line[i] != '\"' && i > -1)
		i = realloc_buffer(data, line, i);
	if (line[i] == '\"')
		i++;
	else
		return (unexpected('\"', data), -1);
	data->buffer[data->bufpos] = '\0';
	expanded = expand_var(&data->buffer[start], data);
	data->buffer = ft_realloc(data->buffer, data->bufsize
			+ (ft_strlen(expanded) + 2), data->bufsize);
	if (!data->buffer)
		return (-1);
	while (j < ft_strlen(expanded))
	{
		data->buffer[start + j] = expanded[j];
		j++;
	}
	return (data->bufpos = start + ft_strlen(expanded), free(expanded), i);
}

int	expand_rest(t_token *token, char *line, t_parsedata *data, int i)
{
	int		start;
	char	*expanded;
	int		j;

	j = 0;
	start = data->bufpos;
	while (line[i] && line[i] != '\'' && line[i] != '\"'
		&& !divisor(line, i, token, data) && i > -1)
		i = realloc_buffer(data, line, i);
	data->buffer[data->bufpos] = '\0';
	expanded = expand_var(&data->buffer[start], data);
	data->buffer = ft_realloc(data->buffer, data->bufsize
			+ (ft_strlen(expanded) + 2), data->bufsize);
	if (!data->buffer)
		return (-1);
	while (j < ft_strlen(expanded))
	{
		data->buffer[start + j] = expanded[j];
		j++;
	}
	data->bufpos = start + ft_strlen(expanded);
	free(expanded);
	return (i);
}

int	realloc_buffer(t_parsedata *data, char *line, int i)
{
	int		newsize;

	newsize = 0;
	if (data->bufpos + 2 >= data->bufsize)
	{
		newsize = data->bufsize * 2;
		data->buffer = ft_realloc(data->buffer, newsize, data->bufsize);
		if (!data->buffer)
			return (-1);
		data->bufsize = newsize;
	}
	data->buffer[data->bufpos++] = line[i];
	i = i + 1;
	return (i);
}
