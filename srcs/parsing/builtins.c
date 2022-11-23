/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:19:57 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/11/23 16:34:27 by ngrenoux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_pwd(char *cmd)
{
	char	*cwd;

	cwd = ft_calloc(sizeof(char *), 1);
	if (!cwd)
	{
		perror("cwd malloc error");
		return ;
	}
	if (ft_strcmp(cmd, "pwd") == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("getcwd error");
		printf("%s\n", cwd);
	}
	free(cwd);
}
