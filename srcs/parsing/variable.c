/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:55:40 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/22 16:18:06 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_pos_dollar(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

char	*replace_variable_to_value(char *command_str, char *name, char *value)
{
	char	*str;
	int		start;
	int		end;
	int		i;
	int		j;

	if (value == NULL)
		value = "\0";
	str = malloc(sizeof(char) * (ft_strlen(command_str)
		- ft_strlen(name) - 1 + ft_strlen(value) + 1));
	if (str == NULL)
		return (NULL);
	start = 0;
	while (command_str && command_str[start])
	{
		if (command_str[start] == '$')
			break;
		start++;
	}
	end = start + ft_strlen(name) + 1;
	i = 0;
	while (i < start)
	{
		str[i] = command_str[i];
		i++;
	}
	j = 0;
	while (value[j] != '\0')
	{
		str[i + j] = value[j];
		j++;
	}
	i += j;
	j = end;
	while (command_str[j] != '\0')
	{
		str[i + j] = command_str[j];
		j++;
	}
	free(command_str);
	return (str);
}

void	interprate_variable(t_command *command)
{
	char	*var_res;
	char	*tmp;
	int		pos;
	int		i;

	if (!command)
		return ;
	i = 0;
	while (command->arg && command->arg[i])
	{
		pos = get_pos_dollar(command->arg[i]);
		if (pos != -1)
		{
			// PENSER A PRENDRE DU $ AU \0 ou " ou '
			tmp = ft_substr(command->arg[i], pos + 1, ft_strlen(command->arg[i]));
			var_res = getenv(tmp);
			command->arg[i] = replace_variable_to_value(command->arg[i], tmp, var_res);
			free(tmp);
		}
		i++;
	}
}

/*
TEST = coucou
echo $TEST					-> coucou
echo '$TEST'				-> $TEST
echo "$TEST"				-> coucou
echo '"$TEST"'				-> "$TEST"
echo "'$TEST'"				-> 'coucou'
echo "test $TEST test"		-> test coucou test
echo 'test $TEST test'		-> test $TEST test
echo "'test $TEST test'"	-> 'test coucou test'
echo '"test $TEST test"'	-> "test $TEST test"
*/
