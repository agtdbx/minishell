/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:55:40 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/24 14:17:53 by aderouba         ###   ########.fr       */
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

char	*get_variable_value(t_list *env, char *name)
{
	t_list	*actual;
	t_var	*tmp;

	actual = env;
	while (actual)
	{
		tmp = (t_var *)actual->content;
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp->value);
		actual = actual->next;
	}
	return ("\0");
}

void	set_variable_value(t_list *env, char *name, char *value)
{
	t_list	*actual;
	t_var	*tmp;

	actual = env;
	while (actual)
	{
		tmp = (t_var *)actual->content;
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		actual = actual->next;
	}
	tmp = malloc(sizeof(t_var));
	if (tmp == NULL)
		return ;
	tmp->name = ft_strdup(name);
	tmp->value = ft_strdup(value);
	actual = ft_lstnew(tmp);
	if (actual == NULL)
	{
		free_var(tmp);
		return ;
	}
	ft_lstadd_back(&env, actual);
}

void	remove_variable(t_list *env, char *name)
{
	t_list	*actual;
	t_list	*next;

	actual = env;
	next = actual->next;
	if (ft_strcmp(((t_var *)actual->content)->name, name) == 0)
	{
		ft_lstdelone(actual, free_var);
		env = next;
		return ;
	}
	while (next)
	{
		if (ft_strcmp(((t_var *)next->content)->name, name) == 0)
		{
			actual->next = next->next;
			ft_lstdelone(next, free_var);
			return ;
		}
		actual = next;
		next = next->next;
	}
}
