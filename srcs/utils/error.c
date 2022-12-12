/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:47:29 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/12 13:28:03 by aderouba         ###   ########.fr       */
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

	if (!str[j] || str[j] == '>' || str[j] == '<')
		return (1);
	ft_printf("Start : |%c|\n", str[j]);
	only_space = 1;
	while (str[j] && str[j] != '<' && str[j] != '>')
	{
		ft_printf("|%c|", str[j]);
		if (str[j] != ' ' && str[j] != '\t')
			only_space = 0;
		j++;
	}
	ft_printf("\n");
	if (only_space)
	{
		ft_printf_fd("Error: invalid redirection\n", 2);
		return (0);
	}
	return (1);
}

int	is_redirection(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (str[i])
	{
		quote = quote_gestion(str[i], quote);
		if (quote == '\0' && (str[i] == '<' || str[i] == '>'))
			return (1);
		i++;
	}
	return (0);
}

int	test_bad_redirection(char *str)
{
	int		i;
	int		j;
	char	quote;

	j = 0;
	quote = '\0';
	if (!is_redirection(str))
		return (0);
	while (str[j])
	{
		quote = quote_gestion(str[j], quote);
		if (quote != '\0')
		{
			j++;
			continue ;
		}
		if (!verif_valid_input(str, j))
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
		if (i == 0)
			j++;
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
