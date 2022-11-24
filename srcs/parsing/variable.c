/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:55:40 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/24 10:22:49 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_frist_quote(char *str, int i, int *text)
{
	while (((str[i] == '\'' && *text != -1) || (str[i] == '"' && *text == 0))
		&& str[i] != '\0')
	{
		if (str[i] == '\'' && *text != -1)
			*text = !(*text);
		else if (str[i] == '"' && *text == 0)
			*text = -1;
		else if (str[i] == '"' && *text == -1)
			*text = 0;
		i++;
	}
	return (i);
}

char	*get_substr(char *str, int *i, int *text)
{
	int		j;
	int		remove_quote;
	char	*res;

	j = 0;
	remove_quote = 0;
	while (str[*i + j] != '\0' && (str[*i + j] != '$' || *text == 1))
	{
		j++;
		if (str[*i + j] == '\'' && *text != -1)
		{
			*text = !(*text);
			remove_quote = !(*text);
		}
	}
	if (str[*i + j] == '"' || str[*i + j - 1] == '"')
		remove_quote += 1;
	res = ft_substr(str, *i, j - remove_quote);
	(*i) += j;
	return (res);
}

char	*add_value_variable(char *res, char *str, int *i)
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
	value = get_variable_value(tmp);
	free(tmp);
	res = ft_strjoin_free_1st_p(res, value);
	*i += j;
	return (res);
}

char	*replace_variable_to_value(char *str)
{
	char	*res;
	char	*tmp;
	int		text;
	int		i;

	res = ft_calloc(sizeof(char), 1);
	if (!res)
		return (str);
	i = 0;
	text = 0;
	while (str[i])
	{
		i = skip_frist_quote(str, i, &text);
		tmp = get_substr(str, &i, &text);
		res = ft_strjoin_free_1st_p(res, tmp);
		free(tmp);
		if (str[i] == '\0')
			break ;
		res = add_value_variable(res, str, &i);
	}
	free(str);
	return (res);
}

void	replace_variables_to_values(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->arg && cmd->arg[i])
	{
		cmd->arg[i] = replace_variable_to_value(cmd->arg[i]);
		i++;
	}
}

/*
FAIT
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
*/

/*
A FAIRE
TEST = coucou
*/
