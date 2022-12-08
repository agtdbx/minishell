/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:09:24 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/12/07 16:59:19 by aderouba         ###   ########.fr       */
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
	set_variable_value(data->env, "0", "");
	set_variable_value(data->env, "1", "");
	set_variable_value(data->env, "2", "");
	set_variable_value(data->env, "3", "");
	set_variable_value(data->env, "4", "");
	set_variable_value(data->env, "5", "");
	set_variable_value(data->env, "6", "");
	set_variable_value(data->env, "7", "");
	set_variable_value(data->env, "8", "");
	set_variable_value(data->env, "9", "");
	set_variable_value(data->env, "$", "");
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
