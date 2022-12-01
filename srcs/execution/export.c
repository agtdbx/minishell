/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:45:16 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/30 16:15:17 by ngrenoux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_sort(t_list *elem1, t_list *elem2)
{
	t_var	*tmp;
	t_var	*tmp2;

	tmp = (t_var *)elem1->content;
	tmp2 = (t_var *)elem2->content;
	return (ft_strcmp(tmp->name, tmp2->name) < 0);
}

void	sort_lst(t_list *lst)
{
	void	*swap;
	t_list	*actual;
	t_list	*next;

	actual = lst;
	next = actual->next;
	while (actual->next != NULL)
	{
		if (!is_sort(actual, next))
		{
			swap = actual->content;
			actual->content = next->content;
			next->content = swap;
			actual = lst;
			next = actual->next;
		}
		else
		{
			actual = next;
			next = next->next;
		}
	}
}

void	print_export(t_list *env)
{
	t_list	*actual;
	t_var	*tmp;

	actual = env;
	sort_lst(actual);
	while (actual)
	{
		tmp = (t_var *)actual->content;
		if (tmp->value && ft_strcmp(tmp->name, "?") != 0)
			ft_printf("declare -x %s=%s\n", tmp->name, tmp->value);
		actual = actual->next;
	}
}

void	export_builtin(t_data *data, t_cmd *cmd)
{
	if (cmd->arg[1] == NULL)
		print_export(data->env_copy);
}

/*
export
	-> Print toutes les variables d'environement

export TEST
	-> Initialise la variable TEST sans valeur
	(N'apparait pas dans env car pas de valeur)

export TEST=VALUE
	-> Initialise la variable TEST avec VALUE

export TEST+=VALUE
	-> Ajout VALUE à la fin de la variable TEST
*/
