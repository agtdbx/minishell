/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:47:29 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/11 18:55:45 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	test_input_bad_redirection(char *str, int *i, int j)
{
	while (str[j + *i] == '<')
		(*i)++;
	if (*i > 0 && str[j + *i] == '>')
	{
		ft_printf_fd("Error: syntax error near", 2);
		ft_printf_fd(" unexpected token `>'\n", 2);
		return (1);
	}
	else if (*i > 2)
	{
		ft_printf_fd("Error: syntax error near", 2);
		ft_printf_fd(" unexpected token `newline'\n", 2);
		return (1);
	}
	return (0);
}

int	test_output_bad_redirection(char *str, int *i, int j)
{
	while (str[j + *i] == '>')
		(*i)++;
	if (*i > 0 && str[j + *i] == '<')
	{
		ft_printf_fd("Error: syntax error near", 2);
		ft_printf_fd(" unexpected token `<'\n", 2);
		return (1);
	}
	else if (*i > 2)
	{
		ft_printf_fd("Error: syntax error near", 2);
		ft_printf_fd(" unexpected token `>'\n", 2);
		return (1);
	}
	return (0);
}

int	verif_valid_input(char *str, int j)
{
	int	only_space;

	only_space = 1;
	while (str[j] && str[j] != '<' && str[j] != '>')
	{
		if (str[j] != ' ' && str[j] != '\t')
			only_space = 0;
		j++;
	}
	if (only_space)
	{
		ft_printf_fd("Error: invalid redirection\n", 2);
		return (-1);
	}
	return (j);
}

int	test_bad_redirection(char *str)
{
	int	i;
	int	j;

	j = 0;
	while (str[j])
	{
		j = verif_valid_input(str, j);
		if (j == -1)
			return (1);
		if (str[j] == '\0')
			return (0);
		i = 0;
		if (test_input_bad_redirection(str, &i, j))
			return (1);
		if (i > 0)
		{
			j += i;
			continue ;
		}
		i = 0;
		if (test_output_bad_redirection(str, &i, j))
			return (i);
		j += i;
	}
	return (0);
}

int	error_arg(t_cmd *cmd)
{
	if (cmd->name && !ft_strcmp(cmd->name, "pwd") && cmd->arg[1] != NULL)
	{
		if (cmd->arg[1][0] == '-')
		{
			g_exit_status = 2;
			ft_printf_fd("Error: pwd: %s: invalid option\n", 2, cmd->arg[1]);
			return (1);
		}
	}
	if (cmd->name && !ft_strcmp(cmd->name, "env") && cmd->arg[1] != NULL)
	{
		if (cmd->arg[1][0] == '-')
		{
			g_exit_status = 125;
			ft_printf_fd("Error: env: %s: invalid option\n", 2, cmd->arg[1]);
			return (1);
		}
		else
		{
			g_exit_status = 127;
			ft_printf_fd("env: \'%s\': unwanted argument\n", 2, cmd->arg[1]);
			return (1);
		}
	}
	return (0);
}
