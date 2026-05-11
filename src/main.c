/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:38:16 by albegar2          #+#    #+#             */
/*   Updated: 2026/05/11 22:20:06 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*shell;
	const char	*prompt;
	char		*user_input;

	print_header();
	if (!argv || !envp)
		return (1);
	shell = shell_init();
	if (!shell)
		return (1);
	shell->envp = copy_env(envp);
	if (!shell->envp)
		return (free_minishell(shell), 1);
	if (argc == 3 && ft_strncmp(argv[1], "-c", 3) == 0)
		return (run_parser(argv[2], shell), free_minishell(shell), 0);
	if (argc != 1)
		return (free_minishell(shell), 1);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	prompt = "\001\033[1;95m\002divashell$ \001\033[0m\002";
	if (!isatty(0))
		return (free_minishell(shell), 1);
	main_loop(&user_input, shell, prompt);
	rl_clear_history();
	return (free_minishell(shell), 0);
}

void	main_loop(char **user_input, t_minishell *shell, const char *prompt)
{
	while (1)
	{
		*user_input = readline(prompt);
		if (!*user_input)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (g_signal == SIGINT)
		{
			shell->last_exit_status = 130;
			g_signal = 0;
		}
		manage_userin(user_input, shell);
	}
}

void	manage_userin(char **user_input, t_minishell *shell)
{
	if (is_empty_line(*user_input) == 0)
	{
		add_history(*user_input);
		if (shell->cmd)
			free_cmd(shell->cmd);
		shell->cmd = NULL;
		if (run_parser(*user_input, shell) == 1)
			free(*user_input);
	}
	free(*user_input);
	*user_input = NULL;
}

int	run_parser(char *user_input, t_minishell *shell)
{
	t_parsedata	*data;
	t_token		*token;

	token = init_token();
	if (!token)
		return (0);
	shell->parser_token = token;
	shell->parser_data = NULL;
	data = init_parsedata(user_input, shell->envp, shell);
	if (!data)
		return (clean_parser_state(shell, token, data, 1));
	shell->parser_data = data;
	if (first_check(user_input, data) != 0)
		return (clean_parser_state(shell, token, data, 0));
	shell->cmd = lexer(user_input, data, token);
	if (!shell->cmd)
		return (clean_parser_state(shell, token, data, 0));
	if (run_exec(shell) == 1)
		return (clean_parser_state(shell, token, data, 1));
	clean_parser_state(shell, token, data, 0);
	return (0);
}

int	run_exec(t_minishell *shell)
{
	if (save_heredocs(shell) == 1)
		return (free_exec(shell), 0);
	execute(shell);
	return (0);
}
