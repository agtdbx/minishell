/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:01:43 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/09 14:28:52 by aderouba         ###   ########.fr       */
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

int	check_minus(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=' && arg[i - 1] == '-')
			return (1);
		i++;
	}
	return (0);
}

int	unset_error(t_cmd *cmd)
{
	if (cmd->arg[1] != NULL)
	{
		if (cmd->arg[1][0] == '-' || check_minus(cmd->arg[1]))
		{
			g_exit_status = 2;
			ft_printf_fd("Error: unset: %s: invalid option\n",
				2, cmd->arg[1]);
			return (1);
		}
		else if (ft_isalpha(cmd->arg[1][0]) == 0 && cmd->arg[1][0] != '_')
		{
			g_exit_status = 1;
			ft_printf_fd("Error: unset: `%s\': not a valid identifier\n",
				2, cmd->arg[1]);
			return (1);
		}
	}
	return (0);
}

void	execute_builtins(t_data *data, t_cmd *cmd)
{
	if (cmd->name && !ft_strcmp(cmd->name, "pwd"))
		print_pwd();
	else if (cmd->name && (!ft_strcmp(cmd->name, "~")
			|| !ft_strcmp(cmd->name, "cd")))
		cd_implement(data->env, cmd);
	else if (cmd->name && !ft_strcmp(cmd->name, "env"))
		env_builtin(data->env);
	else if (cmd->name && !ft_strcmp(cmd->name, "export")
		&& !export_error(cmd))
		export_builtin(data, cmd);
	else if (cmd->name && !ft_strcmp(cmd->name, "unset")
		&& !unset_error(cmd))
		unset_builtin(data, cmd);
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
		if (!unset_error(cmd))
			unset_builtin(data, cmd);
		return (1);
	}
	if (ft_strcmp(cmd->name, "export") == 0 && cmd->arg[0] != NULL
		&& cmd->arg[1] != NULL)
	{
		if (!export_error(cmd))
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
