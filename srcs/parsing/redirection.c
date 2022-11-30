/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:51:43 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/29 16:45:43 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_file(char *name, int flags)
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

void	write_in_here_doc_file(int fd, char *limiter)
{
	char	*to_write;
	char	*stop;
	char	*tmp;

	to_write = malloc(sizeof(char));
	if (!to_write)
		return ;
	to_write[0] = '\0';
	stop = ft_strjoin(limiter, "\n");
	while (1)
	{
		tmp = get_next_line(0);
		if (tmp == NULL || ft_strcmp(tmp, stop) == 0)
			break ;
		to_write = ft_strjoin_free_1st_p(to_write, tmp);
		free(tmp);
	}
	if (fd != -1)
		ft_putstr_fd(to_write, fd);
	free(to_write);
	free(stop);
	free(tmp);
}

int	here_doc(char *name)
{
	int	res;
	int	tmp;

	unlink(".heredoc");
	tmp = open(".heredoc", O_RDWR | O_TRUNC | O_CREAT, 0644);
	write_in_here_doc_file(tmp, name);
	close(tmp);
	res = open(".heredoc", O_RDONLY);
	return (res);
}

char	*interprete_redirection(t_cmd *cmd, char *input)
{
	char	**split_res;
	char	*res;
	char	*tmp;
	int		i;
	int		file_next;

	res = ft_calloc(sizeof(char), 1);
	if (!res)
		return (NULL);
	split_res = ft_split_quote(input, " \t");
	i = 0;
	file_next = 0;
	tmp = NULL;
	while (split_res[i])
	{
		if (file_next == 1)
		{
			if (cmd->fd_in > 2)
				close(cmd->fd_in);
			if (tmp)
			{
				cmd->fd_in = check_file(tmp, O_RDONLY);
				free(tmp);
				tmp = NULL;
			}
			else
				cmd->fd_in = check_file(split_res[i], O_RDONLY);
			if (cmd->fd_in == -1)
			{
				ft_lstr_free(split_res);
				return (res);
			}
			file_next = 0;
		}
		else if (file_next == 2)
		{
			if (cmd->fd_out > 2)
				close(cmd->fd_out);
			if (tmp)
			{
				cmd->fd_in = here_doc(tmp);
				free(tmp);
				tmp = NULL;
			}
			else
				cmd->fd_out = here_doc(split_res[i]);
			if (cmd->fd_out == -1)
			{
				ft_lstr_free(split_res);
				return (res);
			}
			file_next = 0;
		}
		else if (file_next == 3)
		{
			if (cmd->fd_out > 2)
				close(cmd->fd_out);
			if (tmp)
			{
				cmd->fd_in = check_file(tmp, O_RDWR | O_TRUNC | O_CREAT);
				free(tmp);
				tmp = NULL;
			}
			else
				cmd->fd_out = check_file(split_res[i], O_RDWR | O_TRUNC | O_CREAT);
			if (cmd->fd_out == -1)
			{
				ft_lstr_free(split_res);
				return (res);
			}
			file_next = 0;
		}
		else if (file_next == 4)
		{
			if (cmd->fd_out > 2)
				close(cmd->fd_out);
			if (tmp)
			{
				cmd->fd_in = check_file(tmp, O_RDWR | O_APPEND | O_CREAT);
				free(tmp);
				tmp = NULL;
			}
			else
				cmd->fd_out = check_file(split_res[i], O_RDWR | O_APPEND | O_CREAT);
			if (cmd->fd_out == -1)
			{
				ft_lstr_free(split_res);
				return (res);
			}
			file_next = 0;
		}
		else if (ft_strcmp(split_res[i], "<") == 0)
			file_next = 1;
		else if (ft_strcmp(split_res[i], "<<") == 0)
			file_next = 2;
		else if (ft_strcmp(split_res[i], ">") == 0)
			file_next = 3;
		else if (ft_strcmp(split_res[i], ">>") == 0)
			file_next = 4;
		else if (ft_strstr(split_res[i], "<<") != NULL)
		{
			if (split_res[i][0] == '<' && split_res[i][1] == '<')
			{
				tmp = ft_substr(split_res[i], 1, ft_strlen(split_res[i]));
				file_next = 2;
			}
			else
			{
				ft_printf_fd("Name invalid, change cette erreur !\n", 2);
				ft_lstr_free(split_res);
				return (res);
			}
		}
		else if (ft_strstr(split_res[i], ">>") != NULL)
		{
			if (split_res[i][0] == '>' && split_res[i][1] == '>')
			{
				tmp = ft_substr(split_res[i], 1, ft_strlen(split_res[i]));
				file_next = 4;
			}
			else
			{
				ft_printf_fd("Name invalid, change cette erreur !\n", 2);
				ft_lstr_free(split_res);
				return (res);
			}
		}
		else if (is_in_char(split_res[i], '<'))
		{
			if (split_res[i][0] == '<')
			{
				tmp = ft_substr(split_res[i], 1, ft_strlen(split_res[i]));
				file_next = 1;
			}
			else
			{
				ft_printf_fd("Name invalid, change cette erreur !\n", 2);
				ft_lstr_free(split_res);
				return (res);
			}
		}
		else if (is_in_char(split_res[i], '>'))
		{
			if (split_res[i][0] == '>')
			{
				tmp = ft_substr(split_res[i], 1, ft_strlen(split_res[i]));
				file_next = 3;
			}
			else
			{
				ft_printf_fd("Name invalid, change cette erreur !\n", 2);
				ft_lstr_free(split_res);
				return (res);
			}
		}
		else
			res = ft_strsuperjoin_free_1st_p(res, split_res[i], " ");
		if (tmp == NULL)
			i++;
	}
	ft_lstr_free(split_res);
	return (res);
}
