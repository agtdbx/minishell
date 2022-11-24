/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:33:10 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/24 10:53:33 by aderouba         ###   ########.fr       */
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
		i++;
	}
}
