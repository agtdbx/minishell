/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:27:16 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/05 14:24:50 by ngrenoux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_init(void)
{
	g_signal.sigint = 0;
	g_signal.sigquit = 0;
	g_signal.exit_status = 0;
	g_signal.pid = 0;
}

void	ctrlc_management(int sig)
{
	(void)sig;
	// printf("\n");
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
	// g_signal.exit_status = 130;
	if (g_signal.pid == 0)
	{
		ft_putstr_fd("\b\b  ", 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("\033[0;36m\033[1m🤬 minishell ▸ \033[0m", 2);
		g_signal.exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", 2);
		g_signal.exit_status = 130;
	}
	g_signal.sigint = 1;
}

void	ft_signals(void)
{
	signal(SIGINT, ctrlc_management);
	signal(SIGQUIT, SIG_IGN);
}
