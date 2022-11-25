/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:19:57 by ngrenoux          #+#    #+#             */
/*   Updated: 2022/11/25 11:43:17 by aderouba         ###   ########.fr       */
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
	char	*home;

	home = get_variable_value(env, "HOME");
	if (ft_strcmp(cmd->arg[0], "~") == 0 && cmd->arg[1] == NULL)
		ft_printf("minishell: %s: Is a directory\n", home);
	else if (ft_strcmp(cmd->arg[0], "cd") == 0
		&& (cmd->arg[1] == NULL || ft_strcmp(cmd->arg[1], "~") == 0))
		chdir(home);
	else if (ft_strcmp(cmd->arg[0], "cd") == 0 && cmd->arg[1])
		chdir(cmd->arg[1]);
}

void	unset_builtin(t_list *env, t_cmd *cmd)
{
	int	i;

	if (!cmd->arg || !cmd->arg[0])
		return ;
	i = 1;
	while (cmd->arg[i])
	{
		remove_variable(env, cmd->arg[i]);
		i++;
	}
}

void	env_builtin(t_list *env)
{
	t_list	*actual;
	t_var	*tmp;

	actual = env;
	while (actual)
	{
		tmp = (t_var *)actual->content;
		if (tmp->value)
			ft_printf("%s=%s\n", tmp->name, tmp->value);
		actual = actual->next;
	}
}
