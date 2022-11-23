/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:50:47 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/11/23 13:51:17 by ngrenoux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char *buf;
	char **paths;
	t_command *commands;

	(void)argc;
	(void)argv;
	paths = get_paths(envp);
	while (1)
	{
		ft_signals();
		buf = readline("> ");
		if (buf == NULL)
		{
			ft_printf("exit\n");
			break;
		}
		if (ft_strcmp(buf, "exit") == 0)
		{
			ft_printf("exit\n");
			break;
		}
		commands = parse_buf(buf, paths);
		free_commands(commands);
		free(buf);
	}
	ft_lstr_free(paths);
	return (0);
}
