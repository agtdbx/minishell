/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:14:56 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/12/01 17:28:09 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_arg_export(t_data *data, char *str)
{
	int		i;
	char	*tmp_str;
	t_var	*tmp;

	i = 0;
	tmp = (t_var *)data->env->content;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (str[i - 1] == '+')
			{
				tmp_str = ft_substr(str, i + 1, ft_strlen(str) - (i + 1));
				if (ft_strncmp(tmp->name, str, i) == 0)
					ft_strcat(tmp->value, tmp_str);
				//dupliquer pour env_copy
			}
		}
		i++;
	}
	free(tmp_str);
	return (0);
}
