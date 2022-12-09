/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 11:52:08 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/09 11:53:33 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_pids(t_data *data, t_cmd *cmds, int **pipes)
{
	int	i;

	i = 0;
	while (cmds[i].input != NULL)
		i++;
	data->pids = malloc(sizeof(int) * i);
	if (!data->pids)
	{
		close_fds(NULL, pipes);
		return (0);
	}
	return (1);
}

void	pipe_gestion(t_cmd *cmds, int i, int *pipe1, int *pipe2)
{
	if (i % 2 == 0)
	{
		if (i > 0)
		{
			pipe(pipe1);
			if (cmds[i].fd_in <= 2)
				cmds[i].fd_in = pipe2[0];
		}
		if (cmds[i + 1].input && cmds[i].fd_out <= 2)
			cmds[i].fd_out = pipe1[1];
	}
	else
	{
		pipe(pipe2);
		if (cmds[i].fd_in <= 2)
			cmds[i].fd_in = pipe1[0];
		if (cmds[i + 1].input && cmds[i].fd_out <= 2)
			cmds[i].fd_out = pipe2[1];
	}
}

void	close_fds(t_cmd *cmd, int **pipes)
{
	if (cmd && cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd && cmd->fd_out > 2)
		close(cmd->fd_out);
	if (pipes && pipes[0] && pipes[0][0] > 2)
		close(pipes[0][0]);
	if (pipes && pipes[0] && pipes[0][1] > 2)
		close(pipes[0][1]);
	if (pipes && pipes[1] && pipes[1][0] > 2)
		close(pipes[1][0]);
	if (pipes && pipes[1] && pipes[1][1] > 2)
		close(pipes[1][1]);
}
