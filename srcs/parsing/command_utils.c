/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:25:30 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/24 12:04:13 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_command_path(char *name, char **paths)
{
	char	*res;
	int		i;

	if (name == NULL || paths == NULL || paths[0] == NULL)
		return (NULL);
	if (access(name, F_OK) == 0 || ft_strcmp(name, "cd") == 0
		|| ft_strcmp(name, "~") == 0)
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
		arg = ft_add_str(arg, split_res[i]);
		i++;
	}
	return (arg);
}
