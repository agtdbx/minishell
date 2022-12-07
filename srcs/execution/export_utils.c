/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:14:56 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/12/05 14:22:22 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	if_char_is_plus(char *str, int i, t_data *data)
{
	char	*tmp_val;
	char	*name;
	char	*value;

	name = ft_substr(str, 0, i - 1);
	value = get_variable_value(data->env, name);
	tmp_val = ft_substr(str, i + 1, ft_strlen(str) - (i + 1));
	value = ft_strjoin(value, tmp_val);
	set_variable_value(data->env, name, value);
	free(value);
	free(tmp_val);
}

void	if_char_is_egal(char *str, int i, t_data *data)
{
	char	*variable_name;
	char	*variable_value;

	if (str[i - 1] == '+')
		if_char_is_plus(str, i, data);
	else
	{
		variable_name = ft_substr(str, 0, i);
		variable_value = ft_substr(str, i + 1, ft_strlen(str) - (i + 1));
		set_variable_value(data->env, variable_name, variable_value);
		free(variable_name);
		free(variable_value);
	}
}

int	check_arg_export(t_data *data, char *str)
{
	int		i;

	if (is_in_char(str, '='))
	{
		i = 0;
		while (str[i] != '=' && str[i])
			i++;
		if_char_is_egal(str, i, data);
	}
	else
		set_variable_value(data->env, str, NULL);
	return (0);
}
