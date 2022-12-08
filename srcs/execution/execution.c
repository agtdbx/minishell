/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:33:10 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/08 14:21:22 by ngrenoux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds(t_cmd *cmd, int *pipe1, int *pipe2)
{
	if (cmd && cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd && cmd->fd_out > 2)
		close(cmd->fd_out);
	if (pipe1 && pipe1[0] > 2)
		close(pipe1[0]);
	if (pipe1 && pipe1[1] > 2)
		close(pipe1[1]);
	if (pipe2 && pipe2[0] > 2)
		close(pipe2[0]);
	if (pipe2 && pipe2[1] > 2)
		close(pipe2[1]);
}

void	execute_cmd(t_list *env, t_cmd *cmd, int *pipe1, int *pipe2)
{
	int		cpid;
	char	**env_tmp;

	cpid = fork();
	ft_signals(2);
	if (cpid == 0)
	{
		if (cmd->name == NULL)
		{
			ft_printf_fd("Error command\n", 2);
			exit(1);
		}
		if (cmd->fd_in > 2)
			dup2(cmd->fd_in, STDIN_FILENO);
		if (cmd->fd_out > 2)
			dup2(cmd->fd_out, STDOUT_FILENO);
		close_fds(cmd, pipe1, pipe2);
		env_tmp = get_tab_env(env);
		execve(cmd->arg[0], cmd->arg, env_tmp);
	}
	waitpid(cpid, NULL, 0);
	close_fds(cmd, NULL, NULL);
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

void	execute_our_cmd(t_data *data, t_cmd *cmd, int *pipe1, int *pipe2)
{
	int	cpid;

	cpid = fork();
	if (cpid == 0)
	{
		if (cmd->fd_in > 2)
			dup2(cmd->fd_in, STDIN_FILENO);
		if (cmd->fd_out > 2)
			dup2(cmd->fd_out, STDOUT_FILENO);
		execute_builtins(data, cmd);
		close_fds(cmd, pipe1, pipe2);
		free_command(cmd);
		free(cmd);
		ft_lstr_free(data->paths);
		ft_lstclear(&data->env, free_var);
		ft_lstr_free(data->heredoc);
		exit(0);
	}
	waitpid(cpid, NULL, 0);
	close_fds(cmd, pipe1, pipe2);
}

void	interprete_cmds(t_data *data, t_cmd *cmds)
{
	int	i;
	int	pipe1[2];
	int	pipe2[2];

	i = 0;
	if (!cmds || !cmds[0].input || data->pipe_error != -1)
		return ;
	pipe(pipe1);
	pipe2[0] = 0;
	pipe2[1] = 1;
	data->exit = -1 - (cmds[1].input != NULL);
	while (cmds[i].input != NULL)
	{
		g_exit_status = 0;
		pipe_gestion(cmds, i, pipe1, pipe2);
		if (cmds[i].name && modify_env(data, &cmds[i]))
			close_fds(&cmds[i], NULL, NULL);
		else if (cmds[i].name && is_bultin(cmds[i].name))
			execute_our_cmd(data, &cmds[i], pipe1, pipe2);
		else if (cmds[i].name)
			execute_cmd(data->env, &cmds[i], pipe1, pipe2);
		i++;
	}
	close_fds(NULL, pipe1, pipe2);
}
