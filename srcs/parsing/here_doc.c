/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:22:40 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/06 11:04:17 by ngrenoux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*write_in_here_doc(char *limiter)
{
	char	*to_write;
	char	*stop;
	char	*tmp;

	to_write = malloc(sizeof(char));
	if (!to_write)
		return (NULL);
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
	return (to_write);
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

void	parse_heredoc(t_data *data, char *buf)
{
	char	*tmp;
	char	*buf_write;
	int		start;
	int		len;
	int		nb_cmd;

	start = 0;
	nb_cmd = 0;
	while (buf[start] && (data->pipe_error == -1 || nb_cmd < data->pipe_error))
	{
		while (!(buf[start] == '<' && buf[start + 1] == '<') && buf[start + 1])
			start++;
		if (buf[start] == '\0' || buf[start + 1] == '\0')
			return ;
		start += 2;
		while ((buf[start] == ' ' || buf[start] == '\t') && buf[start])
			start++;
		len = 0;
		while (buf[start + len] != ' ' && buf[start + len] != '\t'
			&& buf[start + len] != '<' && buf[start + len] != '>' && buf[start])
			len++;
		tmp = ft_substr(buf, start, len);
		buf_write = write_in_here_doc(tmp);
		free(tmp);
		data->heredoc = ft_add_str(data->heredoc, buf_write);
		start += len;
		nb_cmd++;
	}
}

char	*get_and_remove_first_heredoc(t_data *data)
{
	char	**heredoc;
	char	*res;
	int		i;

	i = 0;
	while (data->heredoc[i])
		i++;
	if (i == 0)
		return (NULL);
	heredoc = malloc(sizeof(char *) * (i));
	if (heredoc == NULL)
		return (NULL);
	res = data->heredoc[0];
	i = 1;
	while (data->heredoc[i])
	{
		heredoc[i - 1] = data->heredoc[i];
		i++;
	}
	heredoc[i - 1] = NULL;
	free(data->heredoc);
	data->heredoc = heredoc;
	return (res);
}

int	here_doc(t_data *data)
{
	int		res;
	int		tmp;
	char	*buf_write;

	unlink(".heredoc");
	tmp = open(".heredoc", O_RDWR | O_TRUNC | O_CREAT, 0644);
	buf_write = get_and_remove_first_heredoc(data);
	ft_putstr_fd(buf_write, tmp);
	free(buf_write);
	close(tmp);
	res = open(".heredoc", O_RDONLY);
	return (res);
}
