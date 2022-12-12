/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:27:37 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/12 18:12:37 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_paths(t_list *env)
{
	char	*tmp;
	char	**res;

	tmp = get_variable_value(env, "PATH");
	res = ft_split(tmp, ':');
	free(tmp);
	return (res);
}

t_cmd	*add_command(t_cmd *commands, t_cmd command)
{
	t_cmd	*res;
	int		i;

	i = 0;
	while (commands != NULL && commands[i].input != NULL)
		i++;
	res = malloc(sizeof(t_cmd) * (i + 2));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (commands != NULL && commands[i].input != NULL)
	{
		res[i] = commands[i];
		i++;
	}
	res[i] = command;
	res[i + 1].input = NULL;
	free(commands);
	return (res);
}

t_cmd	*parse_buf(t_data *data, char *buf, char **paths)
{
	t_cmd	*commands;
	t_cmd	tmp;
	char	**inputs;
	int		i;

	commands = malloc(sizeof(t_cmd));
	if (commands == NULL)
		return (NULL);
	commands[0].input = NULL;
	inputs = ft_split_quote(buf, "|");
	if (inputs == NULL)
	{
		free(commands);
		return (NULL);
	}
	i = 0;
	while (inputs[i] != NULL)
	{
		tmp = get_cmd(data, inputs[i], paths);
		ft_printf("COMMAND\ninput : %s\nname : %s\narg :", tmp.input, tmp.name);
		for (int j = 0;  tmp.arg && tmp.arg[j]; j++)
			ft_printf("|%s| ", tmp.arg[j]);
		ft_printf("\nin %i\nout : %i\n\n", tmp.fd_in, tmp.fd_out);
		commands = add_command(commands, tmp);
		i++;
	}
	free(inputs);
	return (commands);
}

void	free_commands(t_cmd *commands)
{
	int	i;

	i = 0;
	while (commands && commands[i].input != NULL)
	{
		free_command(&commands[i]);
		i++;
	}
	if (commands)
		free(commands);
}
