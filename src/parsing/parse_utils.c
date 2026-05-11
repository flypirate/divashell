/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:33:10 by albegar2          #+#    #+#             */
/*   Updated: 2026/05/11 22:07:32 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

int	check_redirs(t_token *token_list)
{
	while (token_list)
	{
		if (token_list->type == REDIRR)
		{
			if (ft_strncmp(token_list->val, "<<", 2) == 0)
				token_list->type = T_HEREDOC;
			else if (ft_strncmp(token_list->val, ">>", 2) == 0)
				token_list->type = T_APPEND;
		}
		token_list = token_list->next;
	}
	return (0);
}

int	divisor(char *line, int i, t_token *token, t_parsedata *data)
{
	int	check;
	int	redir;

	check = 0;
	if (line[i] && ft_isspace(line[i]))
		check = 1;
	redir = is_redirection(&line[i], token, data);
	if (redir != -1)
	{
		check = 1;
		i = i + redir;
	}
	else if (is_pipe(&line[i], token, data) == 0)
	{
		check = 1;
		i++;
	}
	return (check);
}

void	check_emptypipe(t_token *token, t_parsedata *data)
{
	while (token)
	{
		if (token->type == PIPE)
		{
			if (!token->next || token->next->type == PIPE)
			{
				data->error = '|';
				return ;
			}
		}
		token = token->next;
	}
}

int	check_files(t_token *token, t_parsedata *data)
{
	while (token)
	{
		if (token->type == T_INFILE || token->type == T_HEREDOC
			|| token->type == T_OUTFILE || token->type == T_APPEND)
		{
			if (!token->next || token->next->type == PIPE
				|| token->next->type == T_INFILE
				|| token->next->type == T_OUTFILE
				|| token->next->type == T_APPEND
				|| token->next->type == T_HEREDOC)
			{
				printf("divashell$: syntax error near unexpected "
					"token 'newline'\n");
				data->shell->last_exit_status = 2;
				return (0);
			}
		}
		token = token->next;
	}
	return (1);
}

int	first_check(char *line, t_parsedata *data)
{
	int	i;

	i = 0;
	if (line[0] == '\0')
		return (1);
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '|')
	{
		printf("divashell$: syntax error near unexpected token '%c'\n",
			line[i]);
		data->shell->last_exit_status = 2;
		return (1);
	}
	return (0);
}
