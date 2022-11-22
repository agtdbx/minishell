/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:50:47 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/11/22 13:54:55 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*buf;
	char		**paths;
	t_command	*commands;

	(void)argc;
	(void)argv;
	paths = get_paths(envp);
	while (1)
	{
		buf = readline("> ");
		if (buf == NULL)
		{
			ft_printf("exit\n");
			break ;
		}
		if (ft_strcmp(buf, "exit") == 0)
			break ;
		commands = parse_buf(buf, paths);
		free_commands(commands);
		free(buf);
	}
	ft_lstr_free(paths);
	return (0);
}
