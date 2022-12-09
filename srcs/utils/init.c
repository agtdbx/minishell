/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:09:24 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/12/08 17:29:57 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	init_data(void)
{
	t_data	data;

	data.env = NULL;
	data.paths = NULL;
	data.heredoc = NULL;
	return (data);
}

void	init_all_variable(t_data *data)
{
	set_variable_value(data->env, "0", NULL);
	set_variable_value(data->env, "1", NULL);
	set_variable_value(data->env, "2", NULL);
	set_variable_value(data->env, "3", NULL);
	set_variable_value(data->env, "4", NULL);
	set_variable_value(data->env, "5", NULL);
	set_variable_value(data->env, "6", NULL);
	set_variable_value(data->env, "7", NULL);
	set_variable_value(data->env, "8", NULL);
	set_variable_value(data->env, "9", NULL);
	set_variable_value(data->env, "$", NULL);
}

t_data	ft_init(char **envp)
{
	t_data	data;

	data = init_data();
	data.env = create_env(envp);
	data.paths = get_paths(data.env);
	data.heredoc = ft_calloc(sizeof(char *), 1);
	data.exit = -1;
	data.pipe_error = -1;
	init_all_variable(&data);
	return (data);
}
