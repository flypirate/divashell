/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 14:49:54 by username          #+#    #+#             */
/*   Updated: 2026/05/11 22:22:36 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSER_H
# define MINISHELL_PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "minishell_exec.h"

typedef struct s_command	t_cmd;
typedef struct s_redir		t_redir;
typedef struct s_minishell	t_minishell;

typedef struct s_parsedata
{
	char			**envp;
	char			**exported;
	char			*buffer;
	t_minishell		*shell;
	char			*expandarg;
	int				divisor;
	int				bufpos;
	int				bufsize;
	int				checkin;
	int				checkout;
	int				checkhere;
	int				checkappend;
	int				redirin;
	int				redirout;
	int				checkpipe;
	char			error;
}		t_parsedata;

typedef enum s_type
{
	WORD,
	REDIRR,
	T_INFILE,
	T_OUTFILE,
	PIPE,
	EXPANSION,
	T_HEREDOC,
	T_APPEND
}	t_type;

typedef struct s_token
{
	char			*val;
	t_type			type;
	struct s_token	*next;
}	t_token;

int			run_parser(char *user_input, t_minishell *shell);
int			first_check(char *line, t_parsedata *data);
int			is_command(char *line, t_parsedata *data);
int			is_file(char *line);
int			is_redirection(char *line, t_token *token, t_parsedata *data);
int			is_expansion(char *line);
char		*expand_var(char *arg, t_parsedata *data);
int			expand_tool(int *j, int *i, t_parsedata *data, char **buffer);
t_cmd		*lexer(char *line, t_parsedata *data, t_token *token);
t_token		*init_token(void);
t_parsedata	*init_parsedata(char *line, char **env, t_minishell *shell);
t_cmd		*control_and_send(t_token *token, t_parsedata *data);
t_cmd		*set_cmdstruct(t_token *token);
t_cmd		*fill_cmdstruct(t_token *token, t_parsedata *data);
int			count_args(t_token *token);
int			is_pipe(char *line, t_token *token, t_parsedata *data);
void		free_all(t_token *token, t_parsedata *data);
void		free_parsedata(t_parsedata *data);
t_token		*manage_args(t_token *token, t_parsedata *data, t_cmd *cmd);
t_token		*if_infile_or_here(t_token *token, t_cmd *cmd, t_parsedata *data);
t_token		*if_out_or_app(t_token *token, t_cmd *cmd, t_parsedata *data);
t_token		*if_arg(t_token *token, t_cmd *cmd, t_parsedata *data);
int			if_redir(t_token *token, t_cmd *cmd, t_parsedata *data);
t_cmd		*if_pipe(t_parsedata *data, t_cmd *cmd, t_token *token);
int			ft_isspace(char arg);
void		free_tokenlist(t_token *token);
int			word_capture(t_token *token, char *line, t_parsedata *data, int i);
t_token		*new_token(t_token *token);
void		reset_flags(t_parsedata *data);
void		unexpected(char line, t_parsedata *data);
int			check_rsyntax(char *line);
t_redir		*set_redir(void);
int			def_redirtype(t_token *token, t_parsedata *data, int i);
t_cmd		*case_pipetype(t_token *token, t_parsedata *data, t_cmd *firstcmd,
				t_cmd	*cmd);
void		case_heredoc(t_token *token, t_redir *redirnode, t_parsedata *data);
void		case_append(t_token *token, t_redir *redirnode, t_parsedata *data);
void		case_infile(t_token *token, t_redir *redirnode, t_parsedata *data);
void		case_outfile(t_token *token, t_redir *redirnode, t_parsedata *data);
char		*find_var(t_parsedata *data, char *exp);
int			add_token(char *line, t_parsedata *data, int i, t_token *token);
char		*set_expvar(char *arg, int *i, t_parsedata *data);
char		*get_exitstatus(t_minishell *shell);
int			realloc_buffer(t_parsedata *data, char *line, int i);
void		free_parsestruct(t_parsedata *data);
int			divisor(char *line, int i, t_token *token, t_parsedata *data);
t_token		*check_divisor(char *line, t_parsedata *data, t_token *token);
int			check_files(t_token *token, t_parsedata *data);
void		check_cmds(t_cmd *command);
void		print_exported(t_parsedata *data);
void		check_emptypipe(t_token *token, t_parsedata *data);
int			expand_double(char *line, t_parsedata *data, int i);
void		print_header();
int			expand_rest(t_token *token, char *line, t_parsedata *data, int i);
int			clean_parser_state(t_minishell *shell, t_token *token,
				t_parsedata *data, int ret);

#endif
