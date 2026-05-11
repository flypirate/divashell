/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 20:11:37 by albegar2          #+#    #+#             */
/*   Updated: 2026/05/11 22:31:14 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

void	free_minishell(t_minishell *shell)
{
	if (!shell)
		return ;
	if (shell->parser_token || shell->parser_data)
		free_all(shell->parser_token, shell->parser_data);
	if (shell->envp)
		free_matrix(shell->envp);
	if (shell->cmd)
		free_cmd(shell->cmd);
	if (shell->pipex)
		free_pipex(shell->pipex);
	free(shell);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line || line[0] == '\0')
		return (1);
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

t_minishell	*shell_init(void)
{
	t_minishell	*shell;

	shell = malloc(sizeof(t_minishell));
	if (!shell)
		return (NULL);
	shell->original_stdout = -1;
	shell->original_stdin = -1;
	shell->pipex = NULL;
	shell->envp = NULL;
	shell->last_exit_status = 0;
	g_signal = 0;
	shell->cmd = NULL;
	shell->parser_token = NULL;
	shell->parser_data = NULL;
	return (shell);
}

int	clean_parser_state(t_minishell *shell, t_token *token,
		t_parsedata *data, int ret)
{
	free_all(token, data);
	shell->parser_token = NULL;
	shell->parser_data = NULL;
	return (ret);
}

void	print_header(void)
{
	char	*line1;
	char	*line2;
	char	*line3;

	line1 = "\033[95m☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠\n\033[0m";
	line2 = "\033[95m        DON'T F*CK WITH ME : )        \n\033[0m";
	line3 = "\033[95m☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠ ☠\n\n\033[0m";
	write(1, line1, strlen(line1));
	write(1, line2, strlen(line2));
	write(1, line3, strlen(line3));
}
