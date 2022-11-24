/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:33:10 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/24 17:36:09 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}


// LEAK QUAND TEST =coucou ou TEST= coucou ou TEST = coucou
void	variable_affectation(t_list *env, char *input)
{
	char	*name;
	char	*value;
	int		start;
	int		len;
	int		i;

	len = 0;
	while (input[len] != '=' && input[len] != ' ')
		len++;
	if (input[len] == ' ')
	{
		ft_printf_fd("INVALID ASIGN\n", 1);
		return ;
	}
	name = ft_substr(input, 0, len);
	start = len + 1;
	len = 0;
	while (input[start + len] != '\0' && input[start + len] != ' ')
		len++;
	i = 0;
	while (input[start + len + i] == ' ')
		i++;
	if (input[start + len + i] != '\0')
	{
		ft_printf_fd("INVALID ASIGN\n", 1);
		free(name);
		return ;
	}
	value = ft_substr(input, start, len);
	value = replace_variable_to_value(env, value);
	set_variable_value(env, name, value);
	free(name);
	free(value);
}

void	variable_first_cmd(t_list *env, t_cmd *cmd)
{
	if (is_in_str(cmd->input, '$'))
		cmd->input = replace_variable_to_value(env, cmd->input);
	if (is_in_str(cmd->input, '='))
		variable_affectation(env, cmd->input);
}

void	interprete_cmds(t_list *env, t_cmd *cmds)
{
	int	i;

	i = 0;
	if (!cmds || !cmds[0].input)
		return ;
	if (cmds[i].name == 0)
		variable_first_cmd(env, &cmds[i]);
	while (cmds[i].input != NULL)
	{
		if (cmds[i].name && ft_strcmp(cmds[i].name, "pwd") == 0)
			print_pwd(&cmds[i]);
		else if (cmds[i].name && (!ft_strcmp(cmds[i].name, "~")
				|| !ft_strcmp(cmds[i].name, "cd")))
			cd_implement(env, &cmds[i]);
		else if (cmds[i].name && !ft_strcmp(cmds[i].name, "unset"))
			unset_builtin(env, &cmds[i]);
		else if (cmds[i].name && !ft_strcmp(cmds[i].name, "env"))
			env_builtin(env);
		i++;
	}
}
