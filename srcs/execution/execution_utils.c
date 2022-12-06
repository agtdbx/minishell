/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:01:43 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/06 12:51:43 by ngrenoux         ###   ########.fr       */
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
	return (0);
}

void	execute_error(t_cmd	*cmd, int status)
{
	if (status != 0)
		ft_printf_fd("%s : status on exit %i\n", 2, cmd->name, status);
}
