/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:33:10 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/09 09:50:54 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds(t_cmd *cmd, int **pipes, int in_fork)
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
	if (in_fork)
	{
	}
}

int	execute_cmd(t_data *data, t_cmd *cmds, int i, int **pipes)
{
	int		cpid;
	char	**env_tmp;

	if (!cmds[i].name)
	{
		close_fds(&cmds[i], NULL, 0);
		return (-1);
	}
	cpid = fork();
	ft_signals(2);
	if (cpid == 0)
	{
		if (cmds[i].fd_in > 2)
			dup2(cmds[i].fd_in, STDIN_FILENO);
		if (cmds[i].fd_out > 2)
			dup2(cmds[i].fd_out, STDOUT_FILENO);
		close_fds(&cmds[i], pipes, 1);
		if (is_bultin(cmds[i].name))
		{
			execute_builtins(data, &cmds[i]);
			free_commands(cmds);
			ft_lstr_free(data->paths);
			ft_lstclear(&data->env, free_var);
			ft_lstr_free(data->heredoc);
			exit(0);
		}
		else
		{
			env_tmp = get_tab_env(data->env);
			execve(cmds[i].arg[0], cmds[i].arg, env_tmp);
			ft_lstr_free(env_tmp);
			ft_lstr_free(data->paths);
			ft_lstclear(&data->env, free_var);
			ft_lstr_free(data->heredoc);
			g_exit_status = 127;
			exit(1);
		}
	}
	waitpid(cpid, NULL, 0);
	close_fds(&cmds[i], NULL, 0);
	return (cpid);
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

void	interprete_cmds(t_data *data, t_cmd *cmds)
{
	int	i;
	int	pipe1[2];
	int	pipe2[2];
	int	*pipes[2];

	i = 0;
	if (!cmds || !cmds[0].input || data->pipe_error != -1)
		return ;
	pipe(pipe1);
	pipe2[0] = 0;
	pipe2[1] = 1;
	pipes[0] = pipe1;
	pipes[1] = pipe2;
	data->exit = -1 - (cmds[1].input != NULL);
	while (cmds[i].input != NULL)
	{
		g_exit_status = 0;
		pipe_gestion(cmds, i, pipes[0], pipes[1]);
		if (data->exit == -1 && cmds[i].name && modify_env(data, &cmds[i]))
			close_fds(&cmds[i], NULL, 0);
		else
			execute_cmd(data, cmds, i, pipes);
		i++;
	}
	close_fds(NULL, pipes, 0);
	if (data->exit == -1 && (cmds[0].fd_in == -1 || cmds[0].fd_out == -1))
		g_exit_status = 1;
}
