/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:25:30 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/09 16:28:10 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_bultin(char *name)
{
	if (!ft_strcmp(name, "cd") || !ft_strcmp(name, "~"))
		return (1);
	if (!ft_strcmp(name, "unset") || !ft_strcmp(name, "export"))
		return (1);
	if (!ft_strcmp(name, "env"))
		return (1);
	if (!ft_strcmp(name, "exit"))
		return (1);
	if (!ft_strcmp(name, "echo") || !ft_strcmp(name, "pwd"))
		return (1);
	if (!ft_strcmp(name, "true") || !ft_strcmp(name, "false"))
		return (1);
	return (0);
}

char	*get_command_path(char *name, char **paths)
{
	char	*res;
	int		i;

	if (name == NULL || ft_strlen(name) == 0 || paths == NULL
		|| paths[0] == NULL)
		return (NULL);
	if ((access(name, X_OK) == 0) || is_bultin(name))
		return (ft_strdup(name));
	i = 0;
	while (paths[i] != NULL)
	{
		res = ft_strsuperjoin(paths[i], name, "/");
		if (!res)
			continue ;
		if (access(res, F_OK) == 0)
			return (res);
		free(res);
		i++;
	}
	return (NULL);
}

char	**get_arg(char **split_res, char **paths)
{
	char	**arg;
	char	*command_path;
	int		i;

	arg = malloc(sizeof(char *));
	if (arg == NULL)
		return (NULL);
	arg[0] = NULL;
	command_path = get_command_path(split_res[0], paths);
	if (command_path == NULL)
	{
		free(arg);
		return (NULL);
	}
	arg = ft_add_str(arg, command_path);
	i = 1;
	while (split_res[i] != NULL)
	{
		split_res[i] = interprete_quote(split_res[i]);
		arg = ft_add_str(arg, split_res[i]);
		i++;
	}
	return (arg);
}

char	**redo_split(char **split_res)
{
	char	*tmp;
	char	**res;
	int		i;

	tmp = ft_calloc(sizeof(char), 1);
	if (!tmp)
		return (split_res);
	i = 0;
	while (split_res[i])
	{
		tmp = ft_strsuperjoin_free_1st_p(tmp, split_res[i], " ");
		i++;
	}
	res = ft_split_quote(tmp, " ");
	free(tmp);
	if (!res)
		return (split_res);
	ft_lstr_free(split_res);
	return (res);
}
