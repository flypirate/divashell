/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 14:50:03 by albegar2          #+#    #+#             */
/*   Updated: 2026/04/26 19:33:03 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

int	count_args(t_token *token)
{
	int	count;

	count = 0;
	if (!token)
		return (0);
	while (token && token->type != PIPE)
	{
		if (token->type == WORD || token->type == EXPANSION)
			count++;
		token = token->next;
	}
	return (count);
}

t_cmd	*fill_cmdstruct(t_token *token, t_parsedata *data)
{
	t_cmd	*cmd;
	t_cmd	*firstcmd;

	cmd = set_cmdstruct(token);
	if (!cmd)
		return (NULL);
	firstcmd = cmd;
	while (token)
	{
		if (token->type == WORD || token->type == EXPANSION)
			token = manage_args(token, data, cmd);
		else if (token->type == T_OUTFILE || token->type == T_APPEND)
			token = if_out_or_app(token, cmd, data);
		else if (token->type == T_INFILE || token->type == T_HEREDOC)
			token = if_infile_or_here(token, cmd, data);
		else if (token->type == PIPE)
		{
			token = token->next;
			cmd = if_pipe(data, cmd, token);
			if (!cmd)
				return (free_cmd(firstcmd), NULL);
		}
	}
	return (cmd->pipe_next = NULL, firstcmd);
}
