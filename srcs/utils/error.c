/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:47:29 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/08 13:24:37 by aderouba         ###   ########.fr       */
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

int	test_bad_redirection(char *str)
{
	int	i;
	int	j;

	j = 0;
	while (str[j])
	{
		while (str[j] && str[j] != '<' && str[j] != '>')
			j++;
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
