/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:19:57 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/11/24 13:19:18 by aderouba         ###   ########.fr       */
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

void	cd_implement(t_list *env, t_cmd *cmd)
{
	char *home;

	home = get_variable_value(env, "HOME");
	if (ft_strcmp(cmd->arg[0], "~") == 0 && cmd->arg[1] == NULL)
		ft_printf("minishell: %s: Is a directory\n", home);
	else if (ft_strcmp(cmd->arg[0], "cd") == 0
		&& (cmd->arg[1] == NULL || ft_strcmp(cmd->arg[1], "~") == 0))
		chdir(home);
	else if (ft_strcmp(cmd->arg[0], "cd") == 0 && cmd->arg[1])
		chdir(cmd->arg[1]);
}
