/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:55:40 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/24 17:12:43 by aderouba         ###   ########.fr       */
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
	tmp = create_new_var(name, value);
	if (!tmp)
		return ;
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
