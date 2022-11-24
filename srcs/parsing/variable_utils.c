/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:55:40 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/24 11:09:55 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*t_list	create_env(char **envp)
{

}*/

char	*get_variable_value(char *name)
{
	char	*res;

	res = getenv(name);
	if (res == NULL)
		res = "\0";
	return (res);
}
