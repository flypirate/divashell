/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:32:12 by albegar2          #+#    #+#             */
/*   Updated: 2026/05/11 21:11:27 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

t_parsedata	*init_parsedata(char *line, char **env, t_minishell *shell)
{
	t_parsedata	*data;

	data = malloc(sizeof(t_parsedata));
	if (!line || !data)
		return (NULL);
	data->bufsize = ft_strlen(line) + 1;
	data->buffer = malloc(sizeof(char) * data->bufsize);
	if (!data->buffer)
		return (NULL);
	data->envp = copy_env(env);
	if (!data->envp)
		return (free(data->buffer), free(data), NULL);
	data->shell = shell;
	data->expandarg = NULL;
	data->checkin = 0;
	data->checkout = 0;
	data->checkhere = 0;
	data->checkappend = 0;
	data->redirin = 0;
	data->redirout = 0;
	data->checkpipe = 0;
	data->bufpos = 0;
	data->error = 0;
	data->divisor = 0;
	return (data);
}

t_redir	*set_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->redir_type = -1;
	redir->heredoc_fd = -1;
	redir->delimiter = NULL;
	redir->file = NULL;
	redir->next = NULL;
	return (redir);
}

t_cmd	*set_cmdstruct(t_token *token)
{
	t_cmd	*command;
	t_redir	*redir;

	command = malloc(sizeof(t_cmd));
	if (!command)
		return (NULL);
	command->args = malloc(sizeof(char *) * (count_args(token) + 1));
	if (!command->args)
		return (free(command), NULL);
	command->redir = NULL;
	command->argcount = 0;
	command->pipe_next = NULL;
	redir = set_redir();
	if (!redir)
		return (free(command->args), free(command), NULL);
	command->redir = redir;
	return (command);
}

t_cmd	*if_pipe(t_parsedata *data, t_cmd *cmd, t_token *token)
{
	cmd->pipe_next = set_cmdstruct(token);
	cmd = cmd->pipe_next;
	data->checkin = 0;
	data->checkout = 0;
	if (!cmd)
		return (NULL);
	return (cmd);
}

t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->val = NULL;
	token->next = NULL;
	token->type = 0;
	return (token);
}
