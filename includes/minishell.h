/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:56:15 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/11/28 16:35:52 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
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
	struct sigaction	sigact;
}	t_data;

/*===================================================================
								PARSING
===================================================================*/

/* ============================parsing.c========================== */
char	**get_paths(t_list *env);
t_cmd	*add_command(t_cmd *commands, t_cmd command);
t_cmd	*parse_buf(t_list *env, char *buf, char **paths);
void	free_commands(t_cmd *commands);

/* =========================parsing_utils.c======================= */
char	quote_gestion(char c, char quote);
int		is_in_char(char *str, char c);
int		len_word(char const *s, char *sep, int i);
char	**ft_split_quote(char const *s, char *sep);

/* ============================command.c========================== */
void	free_command(t_cmd *command);
t_cmd	empty_command(char *input);
t_cmd	get_cmd(t_list *env, char *input, char **envp);
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
void	set_variable_value(t_list *env, char *name, char *value);
void	remove_variable(t_list *env, char *name);
char	**get_tab_env(t_list *env);

/* ========================variable_utils2.c====================== */
char	*get_name_envp(char *str);
char	*get_value_envp(char *str);
t_var	*create_var(t_list *env, char **envp, int i);
t_list	*create_env(char **envp);
t_var	*create_new_var(char *name, char *value);

/*===================================================================
								SIGNALS
===================================================================*/

/*=============================signal.c============================*/
void	ft_signals(void);

/*===================================================================
								EXECUTION
===================================================================*/

/*===========================execution.c===========================*/
void	interprete_cmds(t_list *env, t_cmd *cmds);

/*============================bultins.c============================*/
char	*ft_pwd(void);
void	print_pwd(void);
void	cd_implement(t_list *env, t_cmd *cmd);
void	unset_builtin(t_list *env, t_cmd *cmd);
void	env_builtin(t_list *env);
void	change_pwd_variable(t_list *env, char *home, t_cmd *cmd, char *tmp);

/*=============================export.c============================*/
void	export_builtin(t_list *env, t_cmd *cmd);

#endif
