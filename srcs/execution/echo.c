/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:31:14 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/12/07 10:11:49 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	option_echo(char **arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1])
			printf(" ");
		i++;
	}
}

void	no_option_echo(char **arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}

void	echo_builtin(t_cmd *cmd)
{
	if (cmd->arg[1])
	{
		if (ft_strcmp(cmd->arg[1], "-n") == 0)
			option_echo(cmd->arg);
		else
			no_option_echo(cmd->arg);
	}
	else
		printf("\n");
}
