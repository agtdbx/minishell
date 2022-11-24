/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:33:10 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/24 11:49:51 by ngrenoux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	interprete_cmds(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds && cmds[i].input != NULL)
	{
		if (cmds[i].name && ft_strcmp(cmds[i].name, "pwd") == 0)
			print_pwd(&cmds[i]);
		else if (cmds[i].name && (!ft_strcmp(cmds[i].name, "~")
			|| !ft_strcmp(cmds[i].name, "cd")))
			cd_implement(&cmds[i]);
		i++;
	}
}
