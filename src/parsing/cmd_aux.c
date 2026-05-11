/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:19:49 by albegar2          #+#    #+#             */
/*   Updated: 2026/04/26 20:27:37 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

t_token	*manage_args(t_token *token, t_parsedata *data, t_cmd *cmd)
{
	if (data->checkin || data->checkout || data->checkappend || data->checkhere)
	{
		if (!if_redir(token, cmd, data))
			return (NULL);
		token = token->next;
	}
	else
		token = if_arg(token, cmd, data);
	return (token);
}

int	if_redir(t_token *token, t_cmd *cmd, t_parsedata *data)
{
	t_redir	*redirnode;
	t_redir	*last;

	redirnode = set_redir();
	if (!redirnode)
		return (0);
	if (cmd->redir == NULL)
		cmd->redir = redirnode;
	else
	{
		last = cmd->redir;
		while (last->next != NULL)
			last = last->next;
		last->next = redirnode;
	}
	if (data->checkhere)
		case_heredoc(token, redirnode, data);
	else if (data->checkin)
		case_infile(token, redirnode, data);
	else if (data->checkappend)
		case_append(token, redirnode, data);
	else if (data->checkout)
		case_outfile(token, redirnode, data);
	return (1);
}

t_token	*if_arg(t_token *token, t_cmd *cmd, t_parsedata *data)
{
	while (data && data->shell)
		break ;
	while (token && (token->type == WORD || token->type == EXPANSION))
	{
		if (!token->val)
			return (cmd->args[cmd->argcount] = NULL, token->next);
		else
			cmd->args[cmd->argcount] = ft_strdup(token->val);
		cmd->argcount++;
		token = token->next;
	}
	cmd->args[cmd->argcount] = NULL;
	return (token);
}

t_token	*if_infile_or_here(t_token *token, t_cmd *cmd, t_parsedata *data)
{
	if (token->type == T_INFILE)
	{
		if (cmd->redir->file != NULL)
		{
			free(cmd->redir->file);
			cmd->redir->file = NULL;
		}
		token = token->next;
		data->checkin = 1;
		return (token);
	}
	else if (token->type == T_HEREDOC)
	{
		data->checkhere = 1;
		token = token->next;
		return (token);
	}
	return (NULL);
}

t_token	*if_out_or_app(t_token *token, t_cmd *cmd, t_parsedata *data)
{
	if (cmd->redir->file != NULL)
	{
		free(cmd->redir->file);
		cmd->redir->file = NULL;
	}
	if (token->type == T_APPEND)
		data->checkappend = 1;
	else
		data->checkout = 1;
	token = token->next;
	return (token);
}
