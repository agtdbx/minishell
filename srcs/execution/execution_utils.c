/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:01:43 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/07 09:56:51 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_builtins(t_data *data, t_cmd *cmd)
{
	if (cmd->name && ft_strcmp(cmd->name, "pwd") == 0)
		print_pwd();
	else if (cmd->name && (!ft_strcmp(cmd->name, "~")
			|| !ft_strcmp(cmd->name, "cd")))
		cd_implement(data->env, cmd);
	else if (cmd->name && !ft_strcmp(cmd->name, "env"))
		env_builtin(data->env);
	else if (cmd->name && !ft_strcmp(cmd->name, "export"))
		export_builtin(data, cmd);
	else if (cmd->name && !ft_strcmp(cmd->name, "echo"))
		echo_builtin(cmd);
	else if (cmd->name && !ft_strcmp(cmd->name, "false"))
		g_exit_status = 1;
	else if (cmd->name && !ft_strcmp(cmd->name, "true"))
		g_exit_status = 0;
}

int	modify_env(t_data *data, t_cmd *cmd)
{
	if (ft_strcmp(cmd->name, "unset") == 0)
	{
		unset_builtin(data, cmd);
		return (1);
	}
	if (ft_strcmp(cmd->name, "export") == 0 && cmd->arg[0] != NULL
		&& cmd->arg[1] != NULL)
	{
		export_builtin(data, cmd);
		return (1);
	}
	if (cmd->name && !ft_strcmp(cmd->name, "exit"))
	{
		exit_builtins(data, cmd);
		return (1);
	}
	return (0);
}
