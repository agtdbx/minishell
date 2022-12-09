/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:33:10 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/09 11:10:15 by aderouba         ###   ########.fr       */
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
		free(data->pids);
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
			ft_printf_fd("SET TO 126\n", 2);
			g_exit_status = 126;
			ft_printf_fd("Error: execution error\n", 2);
			ft_lstr_free(env_tmp);
			free_commands(cmds);
			ft_lstr_free(data->paths);
			ft_lstclear(&data->env, free_var);
			ft_lstr_free(data->heredoc);
			exit(1);
		}
	}
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

	if (!cmds || !cmds[0].input || data->pipe_error != -1)
		return ;
	pipe(pipe1);
	pipe2[0] = 0;
	pipe2[1] = 1;
	pipes[0] = pipe1;
	pipes[1] = pipe2;
	data->exit = -1 - (cmds[1].input != NULL);
	i = 0;
	while (cmds[i].input != NULL)
		i++;
	data->pids = malloc(sizeof(int) * i);
	if (data->pids == NULL)
	{
		close_fds(NULL, pipes, 0);
		return ;
	}
	i = 0;
	while (cmds[i].input != NULL)
	{
		data->pids[i] = -2;
		pipe_gestion(cmds, i, pipes[0], pipes[1]);
		if (data->exit == -1 && cmds[i].name && modify_env(data, &cmds[i]))
			close_fds(&cmds[i], NULL, 0);
		else
			data->pids[i] = execute_cmd(data, cmds, i, pipes);
		i++;
	}
	close_fds(NULL, pipes, 0);
	i = 0;
	while (cmds[i].input != NULL)
	{
		if (data->pids[i] == -1)
		{
			g_exit_status = 127;
			ft_printf_fd("SET TO 127\n", 2);
		}
		else if (data->pids[i] != -2)
		{
			waitpid(data->pids[i], NULL, 0);
			if (data->exit != -1)
			{
				g_exit_status = 0;
				ft_printf_fd("SET TO 0\n", 2);
			}
		}
		i++;
	}
	if (data->exit == -1 && (cmds[0].fd_in == -1 || cmds[0].fd_out == -1))
	{
		g_exit_status = 1;
		ft_printf_fd("SET TO 1\n", 2);
	}
	free(data->pids);
}
