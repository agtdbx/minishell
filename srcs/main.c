/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:50:47 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/12/06 10:59:58 by ngrenoux         ###   ########.fr       */
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
	ft_printf("exit\n");
	unlink(".heredoc");
	exit(0);
}

void	pipe_error(t_data *data, char *buf)
{
	int	i;
	int	nb_cmd;
	int	only_space;

	data->pipe_error = -1;
	i = 0;
	nb_cmd = 0;
	only_space = 1;
	while (buf[i])
	{
		if (buf[i] == '|')
		{
			if (only_space)
			{
				data->pipe_error = nb_cmd;
				ft_printf_fd("minishell: syntax error near unexpected token `|'\n", 2);
				return ;
			}
			nb_cmd++;
			only_space = 1;
		}
		else if (buf[i] != ' ' && buf[i] != '\t')
			only_space = 0;
		i++;
	}
	if (only_space)
	{
		data->pipe_error = nb_cmd;
		ft_printf_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return ;
	}
}

void	parse_and_do_commands(t_data *data, char *buf)
{
	t_cmd	*cmds;

	pipe_error(data, buf);
	parse_heredoc(data, buf);
	cmds = parse_buf(data, buf, data->paths);
	interprete_cmds(data, cmds);
	if (cmds)
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
	}
	return (0);
}
