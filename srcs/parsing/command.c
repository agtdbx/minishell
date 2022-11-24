/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:24:06 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/24 10:17:22 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_command(t_command *command)
{
	if (command == NULL)
		return ;
	if (command->name != NULL)
		free(command->name);
	if (command->input != NULL)
		free(command->input);
	ft_lstr_free(command->arg);
}

t_command	empty_command(char *input)
{
	t_command	command;

	command.name = NULL;
	command.input = input;
	command.arg = NULL;
	command.fd_in = -1;
	command.fd_out = -1;
	return (command);
}

t_command	get_command(char *input, char **paths)
{
	t_command	command;
	char		**split_res;

	if (input == NULL)
		return (empty_command(input));
	command = empty_command(input);
	split_res = ft_split_quote(input, ' ');
	if (split_res == NULL || split_res[0] == NULL)
		return (empty_command(input));
	command.name = split_res[0];
	command.arg = get_arg(split_res, paths);
	if (command.arg == NULL)
	{
		command.input = NULL;
		free(split_res);
		free_command(&command);
		return (empty_command(input));
	}
	command.fd_in = 1;
	command.fd_out = 0;
	free(split_res);
	return (command);
}

void	print_command(t_command *command)
{
	int	i;

	if (!command)
		return ;
	ft_printf("COMMAND\nINPUT :%s\nNAME : %s\nARG : ",
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
