/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:50:47 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/11/24 10:48:27 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_minishell(char *buf, char **paths)
{
	if (buf)
		free(buf);
	rl_clear_history();
	ft_lstr_free(paths);
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*buf;
	char	**paths;
	t_cmd	*cmds;

	(void)argc;
	(void)argv;
	paths = get_paths(envp);
	while (1)
	{
		ft_signals();
		buf = readline("minishell > ");
		if (buf == NULL)
			exit_minishell(buf, paths);
		if (ft_strlen(buf) > 0)
			add_history(buf);
		if (ft_strcmp(buf, "exit") == 0)
			exit_minishell(buf, paths);
		cmds = parse_buf(buf, paths);
		interprete_cmds(cmds);
		free_commands(cmds);
		free(buf);
	}
	rl_clear_history();
	ft_lstr_free(paths);
	return (0);
}
