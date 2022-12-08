/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:01:43 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/08 16:55:25 by ngrenoux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_arg(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->name, "pwd") && cmd->arg[1] != NULL)
	{
		if (cmd->arg[1][0] == '-')
		{
			g_exit_status = 2;
			ft_printf_fd("Error: pwd: %s: invalid option\n", 2, cmd->arg[1]);
		}
		return (1);
	}
	if (!ft_strcmp(cmd->name, "env") && cmd->arg[1] != NULL)
	{
		if (cmd->arg[1][0] == '-')
		{
			g_exit_status = 125;
			ft_printf_fd("Error: env: %s: invalid option\n", 2, cmd->arg[1]);
		}
		else
		{
			g_exit_status = 127;
			ft_printf_fd("env: \'%s\': unwanted argument\n", 2, cmd->arg[1]);
		}
		return (1);
	}
	return (0);
}

int	export_error(t_cmd *cmd)
{
	if (cmd->arg[1] != NULL)
	{
		if (cmd->arg[1][0] == '-')
		{
			g_exit_status = 2;
			ft_printf_fd("Error: export: %s: invalid option", 2, cmd->arg[1]);
		}
		else if (!ft_isalpha(cmd->arg[1][0]) && cmd->arg[1][0] != '_')
		{
			g_exit_status = 1;
			ft_printf_fd("Error: export: `%s\': not a valid identifier",
				2, cmd->arg[1]);
		}
		return (1);
	}
	return (0);
}

void	execute_builtins(t_data *data, t_cmd *cmd)
{
	if (cmd->name && !ft_strcmp(cmd->name, "pwd") && !error_arg(cmd))
		print_pwd();
	else if (cmd->name && (!ft_strcmp(cmd->name, "~")
			|| !ft_strcmp(cmd->name, "cd")))
		cd_implement(data->env, cmd);
	else if (cmd->name && !ft_strcmp(cmd->name, "env") && !error_arg(cmd))
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
		&& cmd->arg[1] != NULL /*&& !export_error(cmd)*/)
	{
		export_builtin(data, cmd);
		return (1);
	}
	if (cmd->name && !ft_strcmp(cmd->name, "exit"))
	{
		exit_builtins(data, cmd);
		return (1);
	}
	if (cmd->name && !ft_strcmp(cmd->name, "cd"))
	{
		cd_implement(data->env, cmd);
		return (1);
	}
	return (0);
}
