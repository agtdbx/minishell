/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:56:15 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/11/24 10:26:28 by aderouba         ###   ########.fr       */
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
char	**get_paths(char **envp);
t_cmd	*parse_buf(char *buf, char **paths);
t_cmd	*add_command(t_cmd *commands, t_cmd command);
t_cmd	*parse_buf(char *buf, char **paths);
void	free_commands(t_cmd *commands);

/* =========================parsing_utils.c======================= */
char	quote_gestion(char c, char quote);
int		len_word(char const *s, char c, int i);
char	**ft_split_quote(char const *s, char c);

/* ============================command.c========================== */
void	free_command(t_cmd *command);
t_cmd	empty_command(char *input);
t_cmd	get_cmd(char *input, char **envp);
void	print_cmd(t_cmd *command);

/* =========================command_utils.c======================= */
char	*get_cmd_path(char *name, char **paths);
char	**get_arg(char **split_res, char **paths);

/* ===========================variable.c========================== */
int		skip_frist_quote(char *str, int i, int *text);
char	*get_substr(char *str, int *i, int *text);
char	*add_value_variable(char *res, char *str, int *i);
char	*replace_variable_to_value(char *str);
void	replace_variables_to_values(t_cmd *cmd);

/* ========================variable_utils.c======================= */
char	*get_variable_value(char *name);

/*===================================================================
								SIGNALS
===================================================================*/

/*=============================signal.c============================*/
void	ft_signals(void);

/*===================================================================
								EXECUTION
===================================================================*/

/*============================bultins.c============================*/
void	print_pwd(t_cmd *cmd);

#endif
