/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:20:44 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/11/25 15:31:24 by ngrenoux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_pwd_variable(t_list *env, char *home, t_cmd *cmd, char *tmp)
{
	if (cmd->arg[1] == NULL || ft_strcmp(cmd->arg[1], "~") == 0)
	{
		if (chdir(home) == 0)
		{
			set_variable_value(env, "OLDPWD", tmp);
			free(tmp);
			tmp = ft_pwd();
			set_variable_value(env, "PWD", tmp);
		}
		free(tmp);
	}
	else if (ft_strcmp(cmd->arg[0], "cd") == 0 && cmd->arg[1])
	{
		if (chdir(cmd->arg[1]) == 0)
		{
			set_variable_value(env, "OLDPWD", tmp);
			free(tmp);
			tmp = ft_pwd();
			set_variable_value(env, "PWD", tmp);
		}
		free(tmp);
	}
}
