/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:09:24 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/12/01 14:11:51 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	init_data(void)
{
	t_data	data;

	data.env = NULL;
	data.env_copy = NULL;
	data.paths = NULL;
	return (data);
}

t_data	ft_init(char **envp)
{
	t_data	data;

	data = init_data();
	data.env = create_env(envp);
	data.env_copy = create_env(envp);
	data.paths = get_paths(data.env);
	return (data);
}
