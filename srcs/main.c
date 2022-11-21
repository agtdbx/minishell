/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:50:47 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/11/21 17:16:05 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
	char *buf;

	while (1)
	{
		buf = readline("> ");
		if (buf == NULL)
		{
			ft_printf("exit\n");
			break ;
		}
			break ;
		if (ft_strcmp(buf, "exit") == 0)
			break ;
		free(buf);
	}
	return (0);
}
