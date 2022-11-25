/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:55:40 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/25 15:10:55 by ngrenoux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*add_char(char *str, char c)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!res)
		return (str);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = '\0';
	free(str);
	return (res);
}

char	*add_chars_before_variable(char *res, char *str, int *i, int *text)
{
	while ((str[*i] != '$' || *text == 1) && str[*i] != '\0')
	{
		if (str[*i] == '\'' && *text != -1)
			*text = !(*text);
		else if (str[*i] == '"' && *text == 0)
			*text = -1;
		else if (str[*i] == '"' && *text == -1)
			*text = 0;
		else
			res = add_char(res, str[*i]);
		(*i)++;
	}
	return (res);
}

char	*add_value_variable(t_list *env, char *res, char *str, int *i)
{
	char	*tmp;
	char	*value;
	int		j;

	(*i)++;
	j = 0;
	while (str[*i + j] != '\0' && str[*i + j] != ' ' && str[*i + j] != '"'
		&& str[*i + j] != '\'' && str[*i + j] != '$')
		j++;
	tmp = ft_substr(str, *i, j);
	value = get_variable_value(env, tmp);
	free(tmp);
	res = ft_strjoin_free_1st_p(res, value);
	*i += j;
	return (res);
}

char	*replace_variable_to_value(t_list *env, char *str)
{
	char	*res;
	int		text;
	int		i;

	res = ft_calloc(sizeof(char), 1);
	if (!res)
		return (str);
	i = 0;
	text = 0;
	while (str[i])
	{
		res = add_chars_before_variable(res, str, &i, &text);
		if (str[i] == '\0')
			break ;
		res = add_value_variable(env, res, str, &i);
	}
	free(str);
	return (res);
}

void	replace_variables_to_values(t_list *env, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->arg && cmd->arg[i])
	{
		cmd->arg[i] = replace_variable_to_value(env, cmd->arg[i]);
		i++;
	}
}

/*
TEST=coucou

echo $TEST					-> coucou
echo '$TEST'				-> $TEST
echo "$TEST"				-> coucou
echo '"$TEST"'				-> "$TEST"
echo "'$TEST'"				-> 'coucou'
echo "test $TEST test"		-> test coucou test
echo 'test $TEST test'		-> test $TEST test
echo "'test $TEST test'"	-> 'test coucou test'
echo '"test $TEST test"'	-> "test $TEST test"
echo "$TEST t $TEST" 		-> coucou t coucou
echo $TEST$TEST				-> coucoucoucou
echo "test"'test'test"test"	-> testtesttesttest

FAIRE UN ADDCHAR
*/
