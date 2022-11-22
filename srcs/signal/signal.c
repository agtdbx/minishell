/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:27:16 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/22 16:48:07 by ngrenoux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Remplace les actions des signaux ctrl + c && ctrl + \ */
void	signals_management(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (sig == SIGINT)
	{
		printf("\n");
		if (info->si_pid == getpid())
			rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT && info->si_pid != getpid())
		ft_putstr_fd("Quit (core dumped)\n", 2);
}

/* Initialisation de la gestion des signaux */
struct sigaction	ft_init_signals(void)
{
	struct sigaction	sigact;
	sigset_t			sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);
	sigaddset(&sigset, SIGQUIT);
	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_mask = sigset;
	sigact.sa_sigaction = &signals_management;
	return (sigact);
}

void	ft_signals(void)
{
	struct sigaction	sigact;

	sigact = ft_init_signals();
	sigaction(SIGINT, &sigact, NULL);
}