/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:09:24 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/12/01 09:24:37 by ngrenoux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	clear_data(void)
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

	data = clear_data();
	data.env = create_env(envp);
	data.env_copy = create_env(envp);
	data.paths = get_paths(data.env);
	return (data);
}
