/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:47:29 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/12 14:26:38 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	test_bad_redirection2(char *str, int j)
{
	int	i;

	i = 0;
	if (test_input_bad_redirection(str, &i, j))
		return (-1);
	if (i > 0)
	{
		j += i;
		return (j);
	}
	i = 0;
	if (test_output_bad_redirection(str, &i, j))
		return (-1);
	j += i;
	if (i == 0)
		j++;
	return (j);
}
