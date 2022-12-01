/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:33:10 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/30 16:20:55 by ngrenoux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds(t_cmd *cmd)
{
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
}

void	execute_cmd(t_list *env, t_cmd *cmd)
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
		close_fds(cmd);
		env_tmp = get_tab_env(env);
		execve(cmd->arg[0], cmd->arg, env_tmp);
	}
	waitpid(cpid, NULL, 0);
	close_fds(cmd);
}

void	interprete_cmds(t_data *data, t_cmd *cmds)
{
	int	i;

	i = 0;
	if (!cmds || !cmds[0].input)
		return ;
	while (cmds[i].input != NULL)
	{
		if (cmds[i].name && ft_strcmp(cmds[i].name, "pwd") == 0)
			print_pwd();
		else if (cmds[i].name && (!ft_strcmp(cmds[i].name, "~")
				|| !ft_strcmp(cmds[i].name, "cd")))
			cd_implement(data->env, &cmds[i]);
		else if (cmds[i].name && !ft_strcmp(cmds[i].name, "unset"))
			unset_builtin(data->env, &cmds[i]);
		else if (cmds[i].name && !ft_strcmp(cmds[i].name, "env"))
			env_builtin(data->env);
		else if (cmds[i].name && !ft_strcmp(cmds[i].name, "export"))
			export_builtin(data, &cmds[i]);
		else
			execute_cmd(data->env, &cmds[i]);
		i++;
	}
}
