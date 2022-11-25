/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:33:10 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/25 11:48:07 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	interprete_cmds(t_list *env, t_cmd *cmds)
{
	int	i;

	i = 0;
	if (!cmds || !cmds[0].input)
		return ;
	while (cmds[i].input != NULL)
	{
		if (cmds[i].name && ft_strcmp(cmds[i].name, "pwd") == 0)
			print_pwd(&cmds[i]);
		else if (cmds[i].name && (!ft_strcmp(cmds[i].name, "~")
				|| !ft_strcmp(cmds[i].name, "cd")))
			cd_implement(env, &cmds[i]);
		else if (cmds[i].name && !ft_strcmp(cmds[i].name, "unset"))
			unset_builtin(env, &cmds[i]);
		else if (cmds[i].name && !ft_strcmp(cmds[i].name, "env"))
			env_builtin(env);
		else if (cmds[i].name && !ft_strcmp(cmds[i].name, "export"))
			export_builtin(env, &cmds[i]);
		i++;
	}
}
