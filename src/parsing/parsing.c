/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quill <quill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:17:22 by albertogm         #+#    #+#             */
/*   Updated: 2026/04/27 01:33:21 by quill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

t_cmd	*lexer(char *line, t_parsedata *data, t_token *token)
{
	int		i;
	t_token	*first;

	i = 0;
	first = token;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (line[i] && !ft_isspace(line[i]))
			i = add_token(line, data, i, token);
		if (i == -1)
		{
			if (data->error)
				unexpected(data->error, data);
			return (NULL);
		}
		token = check_divisor(line, data, token);
		if (!token)
			return (NULL);
	}
	return (control_and_send(first, data));
}

t_token	*check_divisor(char *line, t_parsedata *data, t_token *token)
{
	if (data->divisor)
	{
		if (data->buffer)
		{
			free(data->buffer);
			data->buffer = NULL;
		}
		data->buffer = malloc(sizeof(char) * ft_strlen(line) + 1);
		if (!data->buffer)
			return (NULL);
		data->divisor = 0;
		data->bufpos = 0;
		token->next = init_token();
		return (token = token->next, token);
	}
	else
		return (token);
}

int	add_token(char *line, t_parsedata *data, int i, t_token *token)
{
	int	redir;

	redir = is_redirection(&line[i], token, data);
	if (redir == -1 && data->error)
		return (-1);
	else if (redir != -1)
	{
		data->divisor = 1;
		i = i + redir;
	}
	else if (is_pipe(&line[i], token, data) == 0)
	{
		data->divisor = 1;
		i++;
	}
	else
		i = word_capture(token, line, data, i);
	if (i == -1)
		return (-1);
	return (i);
}

int	word_capture(t_token *token, char *line, t_parsedata *data, int i)
{
	data->bufpos = 0;
	while (line[i] && !divisor(line, i, token, data))
	{
		token->type = EXPANSION;
		if (line[i] == '\'')
		{
			token->type = WORD;
			i++;
			while (line[i] && line[i] != '\'')
				data->buffer[data->bufpos++] = line[i++];
			if (line[i] == '\'')
				i++;
			else
				return (unexpected('\'', data), -1);
		}
		else if (line[i] == '\"')
			i = expand_double(line, data, i + 1);
		else
			i = expand_rest(token, line, data, i);
		if (i == -1)
			return (-1);
	}
	data->buffer[data->bufpos] = '\0';
	return (token->val = ft_strdup(data->buffer), data->divisor = 1, i);
}

t_cmd	*control_and_send(t_token *token, t_parsedata *data)
{
	t_token	*first;
	t_cmd	*command;

	first = token;
	check_emptypipe(first, data);
	if (data->error)
	{
		unexpected(data->error, data);
		return (NULL);
	}
	if (!check_files(first, data))
		return (NULL);
	command = fill_cmdstruct(first, data);
	if (!command)
		return (NULL);
	return (command);
}
