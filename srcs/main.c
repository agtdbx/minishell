/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:50:47 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/11/29 16:46:58 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_minishell(char *buf, char **paths, t_list *env)
{
	if (buf)
		free(buf);
	rl_clear_history();
	ft_lstr_free(paths);
	ft_lstclear(&env, free_var);
	ft_printf("exit\n");
	unlink(".heredoc");
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*buf;
	char	**paths;
	t_cmd	*cmds;
	t_list	*env;

	(void)argc;
	(void)argv;
	env = create_env(envp);
	paths = get_paths(env);
	set_variable_value(env, "?", "0");
	while (1)
	{
		ft_signals();
		buf = readline("minishell > ");
		if (buf == NULL)
			exit_minishell(buf, paths, env);
		if (ft_strlen(buf) > 0)
			add_history(buf);
		if (ft_strcmp(buf, "exit") == 0)
			exit_minishell(buf, paths, env);
		cmds = parse_buf(env, buf, paths);
		interprete_cmds(env, cmds);
		free_commands(cmds);
		free(buf);
		ft_lstr_free(paths);
		paths = get_paths(env);
	}
	return (0);
}
