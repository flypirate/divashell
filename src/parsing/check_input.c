/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quill <quill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:53:33 by albertogm         #+#    #+#             */
/*   Updated: 2026/04/27 12:44:17 by quill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

int	is_redirection(char *line, t_token *token, t_parsedata *data)
{
	int		i;
	char	redir;

	i = 0;
	redir = *line;
	data->redirin = 0;
	data->redirout = 0;
	if (!line[i] || (line[i] != '>' && line[i] != '<'))
		return (-1);
	while (line[i] && (line[i] == redir))
	{
		if (ft_strncmp(line, "<", 1) == 0)
			data->redirin++;
		else if (ft_strncmp(line, ">", 1) == 0)
			data->redirout++;
		i++;
	}
	if (data->redirin > 2 || data->redirout > 2)
		return (data->error = redir, -1);
	if (check_rsyntax(&line[i]) == 1 || line[i] == '|')
		return (data->error = line[i], -1);
	return (def_redirtype(token, data, i));
}

int	def_redirtype(t_token *token, t_parsedata *data, int i)
{
	if (data->redirin == 1)
		return (token->type = T_INFILE, i);
	else if (data->redirout == 1)
		return (token->type = T_OUTFILE, i);
	else if (data->redirin == 2)
		return (token->type = T_HEREDOC, i);
	else if (data->redirout == 2)
		return (token->type = T_APPEND, i);
	return (-1);
}

int	is_expansion(char *line)
{
	int	i;

	i = 0;
	if (line[i] && line[i] == '\"')
		return (0);
	else
		return (1);
}

int	is_pipe(char *line, t_token *token, t_parsedata *data)
{
	data->checkpipe = 0;
	if (ft_strncmp(line, "|", 1) == 0)
	{
		while (line && (ft_strncmp(line, "|", 1) == 0))
		{
			line++;
			data->checkpipe++;
		}
	}
	if (data->checkpipe == 1)
		return (token->type = PIPE, 0);
	else if (data->checkpipe > 1)
		return (data->error = '|', 1);
	else
		return (1);
}

int	check_rsyntax(char *line)
{
	line--;
	if (line[0] == '>')
	{
		if (line[1])
		{
			if (line[1] == '<')
				return (1);
		}
	}
	if (line[0] == '<')
	{
		if (line[1])
		{
			if (line[1] == '>')
				return (1);
		}
	}
	return (0);
}
