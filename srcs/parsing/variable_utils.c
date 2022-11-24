/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:55:40 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/24 12:03:08 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_var(void *var)
{
	t_var	*tmp;
	tmp = (t_var *)var;
	if (tmp->name)
		free(tmp->name);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
}


char	*get_name_envp(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && str[len] != '=')
		len++;
	return (ft_substr(str, 0, len));
}

char	*get_value_envp(char *str)
{
	int	i;
	int	len;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (NULL);
	i++;
	len = i;
	while (str[i + len] != '\0')
		len++;
	return (ft_substr(str, i, len));
}

t_list	*create_env(char **envp)
{
	t_list	*env;
	t_list	*tmp;
	t_var	*var;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		var = malloc(sizeof(t_var));
		if (var == NULL)
		{
			ft_lstclear(&env, free_var);
			return (NULL);
		}
		var->name = get_name_envp(envp[i]);
		var->value = get_value_envp(envp[i]);
		tmp = ft_lstnew(var);
		if (tmp == NULL)
		{
			free_var(var);
			ft_lstclear(&env, free_var);
			return (NULL);
		}
		ft_lstadd_back(&env, tmp);
		i++;
	}
	return (env);
}

char	*get_variable_value(char *name)
{
	char	*res;

	res = getenv(name);
	if (res == NULL)
		res = "\0";
	return (res);
}
