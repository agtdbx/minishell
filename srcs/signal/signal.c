/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:27:16 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/05 15:41:48 by ngrenoux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_init(void)
{
	g_signal.exit_status = 0;
	g_signal.pid = 0;
}

void	sig_management(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal.exit_status = 130;
	}
}

void	ft_signals(void)
{
	signal(SIGINT, sig_management);
	signal(SIGQUIT, SIG_IGN);
}
