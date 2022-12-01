/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:33:10 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/01 11:24:48 by aderouba         ###   ########.fr       */
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

void	execute_builtins(t_data *data, t_cmd *cmds, int i)
{
	if (cmds[i].name && ft_strcmp(cmds[i].name, "pwd") == 0)
		print_pwd();
	else if (cmds[i].name && (!ft_strcmp(cmds[i].name, "~")
			|| !ft_strcmp(cmds[i].name, "cd")))
		cd_implement(data->env, &cmds[i]);
	else if (cmds[i].name && !ft_strcmp(cmds[i].name, "unset"))
		unset_builtin(data, &cmds[i]);
	else if (cmds[i].name && !ft_strcmp(cmds[i].name, "env"))
		env_builtin(data->env);
	else if (cmds[i].name && !ft_strcmp(cmds[i].name, "export"))
		export_builtin(data, &cmds[i]);
}

void	interprete_cmds(t_data *data, t_cmd *cmds)
{
	int	i;
	int	pipe1[2];
	int	pipe2[2];

	i = 0;
	if (!cmds || !cmds[0].input)
		return ;
	pipe(pipe1);
	pipe2[0] = 0;
	pipe2[1] = 1;
	while (cmds[i].input != NULL)
	{
		pipe_gestion(cmds, i, pipe1, pipe2);
		if (cmds[i].name && is_bultin(cmds[i].name))
			execute_builtins(data, cmds, i);
		else if (cmds[i].name)
			execute_cmd(data->env, &cmds[i], pipe1, pipe2);
		i++;
	}
	close_fds(NULL, pipe1, pipe2);
}
