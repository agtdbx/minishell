/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:01:43 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/05 12:19:29 by aderouba         ###   ########.fr       */
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
	else if (cmd->name && !ft_strcmp(cmd->name, "unset"))
		unset_builtin(data, cmd);
	else if (cmd->name && !ft_strcmp(cmd->name, "env"))
		env_builtin(data->env);
	else if (cmd->name && !ft_strcmp(cmd->name, "export"))
		export_builtin(data, cmd);
}
