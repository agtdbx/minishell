/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:24:06 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/06 16:05:49 by ngrenoux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_command(t_cmd *command)
{
	if (command == NULL)
		return ;
	if (command->name != NULL)
		free(command->name);
	if (command->input != NULL)
		free(command->input);
	ft_lstr_free(command->arg);
	if (command->fd_in > 2)
		close(command->fd_in);
	if (command->fd_out > 2)
		close(command->fd_out);
}

t_cmd	empty_command(char *input)
{
	t_cmd	command;

	command.name = NULL;
	command.input = input;
	command.arg = NULL;
	command.fd_in = -1;
	command.fd_out = -1;
	return (command);
}

t_cmd	command_not_found(t_cmd *command, char *input)
{
	if (command->name && ft_strlen(command->name) > 0)
	{
		g_exit_status = 127;
		ft_printf_fd("%s: command not found\n", 2, command->name);
	}
	if (command->fd_in > 2)
		close(command->fd_in);
	if (command->fd_out > 2)
		close(command->fd_out);
	command->input = NULL;
	free_command(command);
	return (empty_command(input));
}

t_cmd	get_cmd(t_data *data, char *input, char **paths)
{
	t_cmd	command;
	char	*input_clean;
	char	**split_res;

	if (input == NULL)
		return (empty_command(input));
	command = empty_command(input);
	command.fd_in = 0;
	command.fd_out = 1;
	input_clean = interprete_redirection(data, &command, input);
	split_res = ft_split_quote(input_clean, " \t");
	free(input_clean);
	if (split_res == NULL || split_res[0] == NULL)
		return (command_not_found(&command, input));
	split_res[0] = replace_variable_to_value(data->env, split_res[0]);
	command.name = split_res[0];
	command.arg = get_arg(split_res, paths);
	free(split_res);
	if (command.arg == NULL)
		return (command_not_found(&command, input));
	return (command);
}

void	print_cmd(t_cmd *command)
{
	int	i;

	if (!command)
		return ;
	ft_printf("COMMAND\nINPUT : %s\nNAME : %s\nARG : ",
		command->input, command->name);
	i = 0;
	if (command->arg)
	{
		ft_printf("{");
		while (command->arg[i])
		{
			ft_printf("%s", command->arg[i]);
			if (command->arg[i + 1])
				ft_printf(" ,");
			i++;
		}
		ft_printf(" , NULL}\n");
	}
	else
		ft_printf("NULL\n");
	ft_printf("Fd in : %i, fd out : %i\n\n", command->fd_in, command->fd_out);
}
