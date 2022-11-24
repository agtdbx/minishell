/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:27:37 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/24 10:22:53 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_paths(char **envp)
{
	int		i;
	int		pos;
	char	*tmp;
	char	**res;

	i = 0;
	pos = -1;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			pos = i;
			break ;
		}
		i++;
	}
	if (pos == -1)
		return (NULL);
	tmp = ft_substr(envp[pos], 5, ft_strlen(envp[pos]));
	res = ft_split(tmp, ':');
	free(tmp);
	return (res);
}

t_cmd	*add_command(t_cmd *commands, t_cmd command)
{
	t_cmd	*res;
	int			i;

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

t_cmd	*parse_buf(char *buf, char **paths)
{
	t_cmd	*commands;
	t_cmd	tmp;
	char		**inputs;
	int			i;

	commands = malloc(sizeof(t_cmd));
	if (commands == NULL)
		return (NULL);
	commands[0].input = NULL;
	inputs = ft_split_quote(buf, '|');
	if (inputs == NULL)
	{
		free(commands);
		return (NULL);
	}
	i = 0;
	while (inputs[i] != NULL)
	{
		tmp = get_cmd(inputs[i], paths);
		replace_variables_to_values(&tmp);
		print_cmd(&tmp);
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
