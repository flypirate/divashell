/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quill <quill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:31:00 by alba              #+#    #+#             */
/*   Updated: 2026/04/27 01:57:54 by quill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include "libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>
# include "minishell_parser.h"

typedef struct s_pipex
{
	int					pipe_fd[2];
	int					prev_fd;
	pid_t				pid;
	pid_t				last_pid;
}						t_pipex;

typedef struct s_token			t_token;
typedef struct s_parsedata		t_parsedata;
extern volatile sig_atomic_t	g_signal;

typedef enum e_redir_type
{
	STDIN_NONE = 0,
	INFILE,
	HEREDOC,
	TRUNC,
	APPEND
}						t_redir_type;

typedef struct s_redir
{
	int					redir_type;
	int					heredoc_fd;
	char				*delimiter;
	char				*file;
	struct s_redir		*next;
}						t_redir;

typedef struct s_command
{
	char				**args;
	t_redir				*redir;
	int					argcount;
	struct s_command	*pipe_next;
}						t_cmd;

typedef struct s_minishell
{
	char				**envp;
	int					original_stdout;
	int					original_stdin;
	int					last_exit_status;
	t_cmd				*cmd;
	t_pipex				*pipex;
	t_token				*parser_token;
	t_parsedata			*parser_data;
}						t_minishell;

t_minishell				*shell_init(void);
int						is_empty_line(char *line);
void					main_loop(char **user_input, t_minishell *shell,
							const char *prompt);
int						run_exec(t_minishell *shell);
char					*resolve_path(char *cmd, char **envp);
void					free_matrix(char **matrix);
void					execute_simple_command(t_minishell *shell);
void					update_exit_status(int status, t_minishell *shell);
void					handle_command_not_found(t_cmd *cmd,
							t_minishell *shell);
int						is_builtin(char *cmd);
void					execute_builtin(t_minishell *shell);
void					builtin_cd(t_minishell *shell, char **args);
void					builtin_echo(char **args, t_minishell *shell);
void					builtin_pwd(char **args, t_minishell *shell);
void					builtin_exit(t_minishell *shell);
void					cleanup_resources(t_minishell *shell);
int						is_name(char *name, char *value);
char					*get_env(char **envp, char *name);
void					set_env(char **envp, char *name, char *value);
char					*cd_path(t_minishell *shell);
char					*cd_reverse(t_minishell *shell);
char					*cd_home(t_minishell *shell);
char					*cd_sort(t_minishell *shell);
char					**copy_env(char **envp);
void					update_cd_path(t_minishell *shell, char *old_pwd,
							char *current_path);
void					execute(t_minishell *shell);
void					child_process(t_minishell *shell, t_cmd *cmd,
							t_pipex *pipex);
void					parent_process(t_pipex *pipex, t_redir *redir,
							t_minishell *shell);
void					redirections(t_cmd *cmd);
int						read_heredoc(t_redir *heredoc, t_minishell *shell);
int						save_heredocs(t_minishell *shell);
void					handle_sigint(int sig);
int						heredoc_signal(int pid, int fd_0, t_minishell *shell);
void					run_commands(t_minishell *shell);
int						env_builtin(t_minishell *shell);
int						export_builtin(char **cmd, t_minishell *shell);
void					free_redir(t_redir *redir);
void					free_cmd(t_cmd *cmd);
void					free_pipex(t_pipex *pipex);
void					save_original_fd(t_minishell *shell);
void					restore_fd(t_minishell *shell);
void					free_exec(t_minishell *shell);
int						unset_builtin(char **cmd, t_minishell *shell);
void					unsetb_helper(t_minishell *shell, int i);
int						print_special_export(t_minishell *shell);
void					free_minishell(t_minishell *shell);
void					handle_dup_pipe_next(t_pipex *pipex);
void					handle_dup_prev_fd(t_pipex *pipex);
int						append_env(char *entry, t_minishell *shell);
int						valid_identifier(char *arg);
int						find_key_index(char **envp, char *arg);
int						env_count(char **envp);
void					sort_env(char **sorted);
int						export_helper(char **cmd, t_minishell *shell, int i);
void					export_setvals(char **cmd, t_minishell *shell, int *i,
							int *j);
void					export_entry(char **entry, char **cmd, int i);
void					exit_helper(t_minishell *shell);
void					manage_userin(char **user_input, t_minishell *shell);

#endif