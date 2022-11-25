/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:45:16 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/25 12:04:53 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_builtin(t_list *env, t_cmd *cmd)
{
	(void)env;
	(void)cmd;
}

/*
export
	-> Print toutes les variables d'environement

export TEST
	-> Initialise la variable TEST sans valeur
	(N'apparait pas dans env car pas de valeur)

export TEST=VALUE
	-> Initialise la variable TEST avec VALUE

export TEST+=VALUE
	-> Ajout VALUE à la fin de la variable TEST
*/
