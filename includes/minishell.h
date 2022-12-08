/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:56:15 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/12/08 13:23:18 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"

/*===================================================================
							STRUCTURES
===================================================================*/

typedef struct s_var
{
	char	*name;
	char	*value;
}	t_var;

typedef struct s_cmd
{
	char	*name;
	char	*input;
	char	**arg;
	int		fd_in;
	int		fd_out;
}	t_cmd;

typedef struct s_data
{
	char				**paths;
	char				**heredoc;
	t_list				*env;
	int					exit;
	int					pipe_error;
}	t_data;

extern int	g_exit_status;

/*===================================================================
								PARSING
===================================================================*/

/* ============================parsing.c========================== */
char	**get_paths(t_list *env);
t_cmd	*add_command(t_cmd *commands, t_cmd command);
t_cmd	*parse_buf(t_data *data, char *buf, char **paths);
void	free_commands(t_cmd *commands);

/* =========================parsing_utils.c======================= */
char	quote_gestion(char c, char quote);
int		is_in_char(char *str, char c);
int		len_word(char const *s, char *sep, int i);
char	**ft_split_quote(char const *s, char *sep);
int		quote_error(char *buf);

/* ============================command.c========================== */
void	free_command(t_cmd *command);
t_cmd	empty_command(char *input);
t_cmd	get_cmd(t_data *data, char *input, char **envp);
void	print_cmd(t_cmd *command);

/* =========================command_utils.c======================= */
int		is_bultin(char *name);
char	*get_cmd_path(char *name, char **paths);
char	**get_arg(char **split_res, char **paths);

/* ===========================variable.c========================== */
char	*add_char(char *str, char c);
char	*add_chars_before_variable(char *res, char *str, int *i, int *text);
char	*add_value_variable(t_list *env, char *res, char *str, int *i);
char	*replace_variable_to_value(t_list *env, char *str);
void	replace_variables_to_values(t_list *env, t_cmd *cmd);

/* ========================variable_utils.c======================= */
void	free_var(void *var);
char	*get_variable_value(t_list *env, char *name);
void	add_new_variable(t_list *env, char *name, char *value);
void	set_variable_value(t_list *env, char *name, char *value);
void	remove_variable(t_list *env, char *name);

/* ========================variable_utils2.c====================== */
char	*get_name_envp(char *str);
char	*get_value_envp(char *str);
t_var	*create_var(t_list *env, char **envp, int i);
t_var	*create_new_var(char *name, char *value);

/* ===============================env.c============================ */
t_list	*create_env(char **envp);
char	**get_tab_env(t_list *env);
t_list	*dup_env(t_list *env);

/* ==========================redirection.c========================= */
int		get_file_next2(char **tmp, char **split_res, int i);
int		get_file_next(char **tmp, char **split_res, int i);
char	*final_check_and_return(int file_next, char **split_res, char *res);
char	*tmp_gestion(char *tmp, char *name, int file_next);
char	*interprete_redirection(t_data *data, t_cmd *cmd, char *input);

/* =======================redirection_utils.c====================== */
int		check_file(char *name, int flags);
void	input_file(t_data *data, t_cmd *cmd, char **name, int heredoc);
void	output_file(t_cmd *cmd, char **name, int append);
char	*error_file(t_cmd *cmd, char *res, char **split_res);
int		get_fd(t_data *data, t_cmd *cmd, char **name, int file_next);

/* =======================redirection_utils2.c===================== */
int		len_word_redirection(char const *s, char *sep, int *i);
char	**ft_split_redirection(char *s);
int		is_pipe_error(t_data *data, int only_space, int nb_cmd);
void	pipe_error(t_data *data, char *buf);

/* ============================here_doc.c========================== */
char	*write_in_here_doc(char *limiter);
void	parse_heredoc(t_data *data, char *buf);
char	*get_and_remove_first_heredoc(t_data *data);
int		here_doc(t_data *data);

/* ==============================error.c=========================== */
int	test_bad_redirection(char *str);

/*===================================================================
								SIGNALS
===================================================================*/

/*=============================signal.c============================*/
void	ft_signals(int sig);

/*===================================================================
								EXECUTION
===================================================================*/

/*===========================execution.c===========================*/
void	close_fds(t_cmd *cmd, int *pipe1, int *pipe2);
void	execute_cmd(t_list *env, t_cmd *cmd, int *pipe1, int *pipe2);
void	pipe_gestion(t_cmd *cmds, int i, int *pipe1, int *pipe2);
void	execute_builtins(t_data *data, t_cmd *cmd);
void	interprete_cmds(t_data *data, t_cmd *cmds);

/*=========================execution_utils.c========================*/
void	execute_our_cmd(t_data *data, t_cmd *cmd, int *pipe1, int *pipe2);
int		modify_env(t_data *data, t_cmd *cmd);

/*============================bultins.c============================*/
char	*ft_pwd(void);
void	print_pwd(void);
void	cd_implement(t_list *env, t_cmd *cmd);
void	unset_builtin(t_data *data, t_cmd *cmd);
void	env_builtin(t_list *env);
void	change_pwd_variable(t_list *env, char *home, t_cmd *cmd, char *tmp);

/*=============================export.c============================*/
void	print_export(t_list *env);
void	export_builtin(t_data *data, t_cmd *cmd);

/*===============================exit.c============================*/
void	exit_builtins(t_data *data, t_cmd *cmd);

/*=============================echo.c==============================*/
void	echo_builtin(t_cmd *cmd);

/*===================================================================
								UTILS
===================================================================*/

/*==============================init.c=============================*/
void	init_all_variable(t_data *data);
t_data	ft_init(char **envp);

/*==========================export_utils.c=========================*/
int		check_arg_export(t_data *data, char *str);

#endif
