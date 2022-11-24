/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:56:15 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/11/24 10:22:33 by ngrenoux         ###   ########.fr       */
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

typedef struct s_command
{
	char	*name;
	char	*input;
	char	**arg;
	int		fd_in;
	int		fd_out;
}	t_command;

typedef struct s_data
{
	struct sigaction	sigact;
}	t_data;

/*===================================================================
								PARSING
===================================================================*/

/* ============================parsing.c========================== */
int			skip_frist_quote(char *str, int i, int *text);
char		*get_substr(char *str, int *i, int *text);
char		*add_value_variable(char *res, char *str, int *i);
char		*replace_variable_to_value(char *str);
void		replace_variables_to_values(t_command *cmd);

/* =========================parsing_utils.c======================= */
char		*get_variable_value(char *name);

/* ============================command.c========================== */
void		free_command(t_command *command);
t_command	empty_command(char *input);
t_command	get_command(char *input, char **envp);
void		print_command(t_command *command);

/* =========================command_utils.c======================= */
char		*get_command_path(char *name, char **paths);
char		**get_arg(char **split_res, char **paths);

/* ===========================variable.c========================== */
char		*get_variable_value(char *name);
int			skip_frist_quote(char *str, int i, int *text);
char		*get_substr(char *str, int *i, int *text);
char		*add_value_variable(char *res, char *str, int *i);
char		*replace_variable_to_value(char *str);
void		replace_variables_to_values(t_command *cmd);

/*===================================================================
								SIGNALS
===================================================================*/

/*=============================signal.c============================*/
void		ft_signals(void);

/*===================================================================
								EXECUTION
===================================================================*/

/*============================bultins.c============================*/
void		print_pwd(t_command *cmd);

#endif
