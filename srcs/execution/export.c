/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:45:16 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/05 10:29:17 by ngrenoux         ###   ########.fr       */
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
	t_list	*cpy;
	t_var	*tmp;
	char	**env_tmp;

	env_tmp = get_tab_env(env);
	cpy = create_env(env_tmp);
	ft_lstr_free(env_tmp);
	sort_lst(cpy);
	actual = cpy;
	sort_lst(actual);
	while (actual)
	{
		tmp = (t_var *)actual->content;
		if (tmp->value && ft_strcmp(tmp->name, "?") != 0)
			ft_printf("declare -x %s=%s\n", tmp->name, tmp->value);
		actual = actual->next;
	}
	ft_lstclear(&cpy, free_var);
}

void	export_builtin(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->arg[1] == NULL)
		print_export(data->env);
	while (cmd->arg[i] != NULL)
	{
		if (check_arg_export(data, cmd->arg[i]))
		{
			ft_printf("Error\n");
			exit(0);
		}
		i++;
	}
}
