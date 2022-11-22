/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:56:15 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/11/22 14:33:21 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"

/*===================================================================
								PARSING
===================================================================*/

typedef struct s_command
{
	char	*name;
	char	*input;
	char	**arg;
	int		fd_in;
	int		fd_out;
}	t_command;

/* ============================parsing.c========================== */
char		**get_paths(char **envp);
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

#endif
