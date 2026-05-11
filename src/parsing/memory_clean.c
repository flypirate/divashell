/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 21:21:28 by albegar2          #+#    #+#             */
/*   Updated: 2026/04/26 22:17:51 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

void	free_all(t_token *token, t_parsedata *data)
{
	free_tokenlist(token);
	free_parsestruct(data);
}

void	free_tokenlist(t_token *token)
{
	t_token	*tmp;

	tmp = NULL;
	while (token)
	{
		tmp = token->next;
		if (token->val)
			free(token->val);
		free(token);
		token = tmp;
	}
}

void	free_parsestruct(t_parsedata *data)
{
	int	i;

	i = 0;
	if (data)
	{
		if (data->buffer)
			free(data->buffer);
		if (data->envp)
		{
			while (data->envp[i])
			{
				free(data->envp[i]);
				i++;
			}
			free(data->envp);
		}
		free(data);
	}
}
