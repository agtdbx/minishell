/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:51:43 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/01 16:13:39 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_file(char *name, int flags)
{
	int	res;

	res = open(name, flags, 0644);
	if (res == -1 || open(name, O_DIRECTORY) != -1)
	{
		ft_printf_fd("minishell: %s: No such file or directory\n", 2, name);
		return (-1);
	}
	return (res);
}

void	input_file(t_data *data, t_cmd *cmd, char **tmp, char *name, int heredoc)
{
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	if (*tmp)
	{
		if (heredoc)
			cmd->fd_in = here_doc(data);
		else
			cmd->fd_in = check_file(*tmp, O_RDONLY);
		free(*tmp);
		*tmp = NULL;
	}
	else
	{
		if (heredoc)
			cmd->fd_in = here_doc(data);
		else
			cmd->fd_in = check_file(name, O_RDONLY);
	}
}

void	output_file(t_cmd *cmd, char **tmp, char *name, int append)
{
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	if (*tmp)
	{
		if (append)
			cmd->fd_out = check_file(*tmp, O_RDWR | O_APPEND | O_CREAT);
		else
			cmd->fd_out = check_file(*tmp, O_RDWR | O_TRUNC | O_CREAT);
		free(*tmp);
		*tmp = NULL;
	}
	else
	{
		if (append)
			cmd->fd_out = check_file(name, O_RDWR | O_APPEND | O_CREAT);
		else
			cmd->fd_out = check_file(name, O_RDWR | O_TRUNC | O_CREAT);
	}
}

char	*error_file(char *res, char **split_res)
{
	ft_lstr_free(split_res);
	return (res);
}

int	get_fd(t_data *data, t_cmd *cmd, char **tmp, char *name, int file_next)
{
	if (file_next == 1)
		input_file(data, cmd, tmp, name, 0);
	else if (file_next == 2)
		input_file(data, cmd, tmp, name, 1);
	else if (file_next == 3)
		output_file(cmd, tmp, name, 0);
	else if (file_next == 4)
		output_file(cmd, tmp, name, 1);
	return (0);
}
