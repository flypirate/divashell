/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:32:55 by quill             #+#    #+#             */
/*   Updated: 2026/05/11 22:33:04 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parser.h"

int	checking_overflow(char *argv)
{
	long long	num;
	int			i;

	i = 0;
	num = 0;
	if (argv[i] == '+' || argv[i] == '-')
		i++;
	while (argv[i])
	{
		if (num > (LLONG_MAX - (argv[i] - '0')) / 10)
			return (1);
		num = num * 10 + (argv[i] - '0');
		i++;
	}
	return (0);
}

int	is_exit_valid(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i = 1;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	if (checking_overflow(arg) == 1)
		return (0);
	return (1);
}

static void	exit_shell(t_minishell *shell, int exitstatus)
{
	restore_fd(shell);
	free_minishell(shell);
	exit(exitstatus);
}

void	builtin_exit(t_minishell *shell)
{
	int	exitstatus;

	exitstatus = shell->last_exit_status;
	if (shell->cmd->pipe_next)
		return (exit_shell(shell, exitstatus));
	if (!shell->cmd->args[1])
	{
		if (isatty(STDIN_FILENO))
			write(1, "\033[1;35msee you never girl lol\033[0m\n", 29);
		return (exit_shell(shell, exitstatus));
	}
	if (shell->cmd->args[2])
	{
		ft_putstr_fd("divashell: exit: too many arguments\n", 2);
		shell->last_exit_status = 1;
		return ;
	}
	exit_helper(shell);
	exitstatus = shell->last_exit_status;
	if (shell->last_exit_status == 11)
		write(1, "you got lucky baby.. xoxo", 25);
	else if (isatty(STDIN_FILENO))
		write(1, "\033[1;35mbye bitch!\033[0m\n", 17);
	return (exit_shell(shell, exitstatus));
}

void	exit_helper(t_minishell *shell)
{
	if (is_exit_valid(shell->cmd->args[1]) == 0)
	{
		if (isatty(STDIN_FILENO))
			write(1, "exit\n", 5);
		ft_putstr_fd("divashell: exit: ", 2);
		ft_putstr_fd(shell->cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		restore_fd(shell);
		free_exec(shell);
		exit(2);
	}
	else
		shell->last_exit_status = (unsigned char)
			ft_atoi(shell->cmd->args[1]);
}
