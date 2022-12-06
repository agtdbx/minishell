/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:28:16 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/05 19:39:34 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*int	is_int(char *str)
{
	int		start;
	int		len;
	long	test;

	start = 0;
	if (str[0] == '-' || str[0] == '+')
		start++;
	while (str[start] == '0')
		start++;
	len = ft_strlen(str);
	if (len == 0 || len - start > 11)
		return (0);
	start = 0;
	if (str[0] == '-' || str[0] == '+')
		start++;
	if (start == 1 && str[start] == '\0')
		return (0);
	while (str[start] >= '0' && str[start] <= '9')
		start++;
	if (start != len)
		return (0);
	test = ft_atol(str);
	if (test > 2147483647 || test < -2147483648)
		return (0);
	return (1);
}*/

/*void	exit_builtins(t_data *data, t_cmd *cmd)
{
	long long	exit_status;
}*/

/*
-9223372036854775807 -> 9223372036854775807

while nb < 0
	nb += 256

while nb > 255
	nb -= 256
*/
