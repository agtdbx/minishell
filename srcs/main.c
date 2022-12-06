/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:50:47 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/12/06 15:31:13 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status;

void	exit_minishell(char *buf, t_data *data)
{
	if (buf)
		free(buf);
	rl_clear_history();
	ft_lstr_free(data->paths);
	ft_lstclear(&data->env, free_var);
	if (data->heredoc)
		free(data->heredoc);
	if (data->exit < 0)
		ft_printf("exit\n");
	unlink(".heredoc");
	exit(data->exit);
}

void	parse_and_do_commands(t_data *data, char *buf)
{
	t_cmd	*cmds;

	if (!quote_error(buf))
	{
		pipe_error(data, buf);
		parse_heredoc(data, buf);
		cmds = parse_buf(data, buf, data->paths);
		interprete_cmds(data, cmds);
		if (cmds)
			free_commands(cmds);
	}
	else
		ft_printf_fd("minishell: quote unclosed\n", 2);
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
	while (1)
	{
		ft_signals(1);
		buf = readline("Minishell: ");
		if (buf == NULL)
			exit_minishell(buf, &data);
		if (ft_strlen(buf) > 0)
			add_history(buf);
		if (ft_strcmp(buf, "exit") == 0)
			exit_minishell(buf, &data);
		parse_and_do_commands(&data, buf);
		data.paths = get_paths(data.env);
		if (data.exit >= 0)
			exit_minishell(NULL, &data);
	}
	return (0);
}
