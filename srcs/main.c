/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:50:47 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/12/01 10:13:30 by aderouba         ###   ########.fr       */
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

void	parse_and_do_commands(t_data *data, char *buf)
{
	t_cmd	*cmds;

	cmds = parse_buf(data->env, buf, data->paths);
	interprete_cmds(data, cmds);
	free_commands(cmds);
	free(buf);
	ft_lstr_free(data->paths);
}

int	main(int argc, char **argv, char **envp)
{
	char	*buf;
	t_data	data;

	(void)argv;
	if (argc != 1)
		return (0);
	data = ft_init(envp);
	set_variable_value(data.env, "?", "0");
	while (1)
	{
		ft_signals();
		buf = readline("Minishell: ");
		if (buf == NULL)
			exit_minishell(buf, data.paths, data.env);
		if (ft_strlen(buf) > 0)
			add_history(buf);
		if (ft_strcmp(buf, "exit") == 0)
			exit_minishell(buf, data.paths, data.env);
		parse_and_do_commands(&data, buf);
		data.paths = get_paths(data.env);
	}
	return (0);
}
