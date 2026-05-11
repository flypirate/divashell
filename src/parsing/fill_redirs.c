/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 20:45:27 by albegar2          #+#    #+#             */
/*   Updated: 2026/03/26 13:56:22 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

void	case_heredoc(t_token *token, t_redir *redirnode, t_parsedata *data)
{
	if (token->val)
		redirnode->delimiter = ft_strdup(token->val);
	redirnode->redir_type = HEREDOC;
	data->checkhere = 0;
}

void	case_append(t_token *token, t_redir *redirnode, t_parsedata *data)
{
	if (token->val)
		redirnode->file = ft_strdup(token->val);
	redirnode->redir_type = APPEND;
	data->checkappend = 0;
}

void	case_infile(t_token *token, t_redir *redirnode, t_parsedata *data)
{
	if (token->val)
		redirnode->file = ft_strdup(token->val);
	redirnode->redir_type = INFILE;
	data->checkin = 0;
}

void	case_outfile(t_token *token, t_redir *redirnode, t_parsedata *data)
{
	if (token->val)
		redirnode->file = ft_strdup(token->val);
	redirnode->redir_type = TRUNC;
	data->checkout = 0;
}
