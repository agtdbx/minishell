/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:56:15 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/11/23 16:27:30 by ngrenoux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../libft/libft.h"

/*===================================================================
								PARSING
===================================================================*/

typedef struct s_command
{
	char *name;
	char *input;
	char **arg;
	int fd_in;
	int fd_out;
} t_command;

typedef struct s_data
{
	struct sigaction	sigact;
}	t_data;

/* ============================parsing.c========================== */
char		 **get_paths(char **envp);
t_command	*add_command(t_command *commands, t_command command);
t_command	*parse_buf(char *buf, char **paths);
void		free_commands(t_command *commands);

/* ============================command.c========================== */
void		free_command(t_command *command);
t_command	empty_command(void);
t_command	get_command(char *input, char **envp);
void		print_command(t_command *command);

/* =========================command_utils.c======================= */
char		*get_command_path(char *name, char **paths);
char		**get_arg(char **split_res, char **paths);

/* ===========================variable.c========================== */
int			get_pos_dollar(char *str);
void		interprate_variable(t_command *command);

/*=============================signal.c============================*/
void	ft_signals(void);

/*============================bultins.c============================*/
void	print_pwd(char *cmd);

#endif
