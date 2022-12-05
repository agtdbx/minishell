/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 09:50:36 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/05 09:55:52 by aderouba         ###   ########.fr       */
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
