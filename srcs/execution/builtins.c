/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:19:57 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/11/24 10:45:25 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_pwd(t_cmd *cmd)
{
	char	*cwd;
	size_t	size;

	if (!cmd || !cmd->name)
		return ;
	size = sizeof(char) * 1024;
	cwd = (char *)malloc(size);
	if (!cwd)
		perror("cwd malloc error");
	if (getcwd(cwd, size) == NULL)
		perror("getcwd error");
	else
		printf("%s\n", cwd);
	free(cwd);
}
