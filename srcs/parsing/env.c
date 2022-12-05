/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 09:50:36 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/05 11:08:28 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		var = create_var(env, envp, i);
		if (var == NULL)
			return (NULL);
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

char	**get_tab_env(t_list *env)
{
	t_list	*actual;
	t_var	*var;
	char	**rep;
	char	*tmp;

	rep = malloc(sizeof(char *));
	if (!rep)
		return (NULL);
	rep[0] = NULL;
	actual = env;
	while (actual)
	{
		var = (t_var *)actual->content;
		tmp = ft_strdup(var->name);
		tmp = ft_strsuperjoin_free_1st_p(tmp, var->value, "=");
		rep = ft_add_str(rep, tmp);
		actual = actual->next;
	}
	return (rep);
}

t_list	*dup_env(t_list *env)
{
	t_list	*actual;
	t_list	*new;
	t_list	*cpy;
	t_var	*var;
	t_var	*tmp;

	actual = env;
	cpy = NULL;
	while (actual)
	{
		tmp = (t_var *)actual->content;
		var = create_new_var(tmp->name, tmp->value);
		if (!var)
		{
			ft_lstclear(&cpy, free_var);
			return (NULL);
		}
		new = ft_lstnew(var);
		if (!new)
		{
			free_var(var);
			ft_lstclear(&cpy, free_var);
			return (NULL);
		}
		ft_lstadd_back(&cpy, new);
		actual = actual->next;
	}
	return (cpy);
}
