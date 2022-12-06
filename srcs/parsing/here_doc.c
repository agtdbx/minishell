/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:22:40 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/06 12:00:04 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*write_in_here_doc(char *limiter)
{
	char	*to_write;
	char	*tmp;

	to_write = malloc(sizeof(char));
	if (!to_write)
		return (NULL);
	to_write[0] = '\0';
	while (1)
	{
		tmp = readline("> ");
		if (tmp == NULL)
		{
			ft_printf_fd("minishell: warning: here-document at line %i", 2, 1);
			ft_printf_fd(" delimited by end-of-file ", 2);
			ft_printf_fd("(wanted `%s')\n", 2, limiter);
			break ;
		}
		else if (ft_strcmp(tmp, limiter) == 0)
			break ;
		tmp = ft_strjoin_free_1st_p(tmp, "\n");
		to_write = ft_strjoin_free_1st_p(to_write, tmp);
		free(tmp);
	}
	return (to_write);
}

int	get_start_limiter(char *buf, int start)
{
	while (!(buf[start] == '<' && buf[start + 1] == '<') && buf[start + 1])
		start++;
	if (buf[start] == '\0' || buf[start + 1] == '\0')
		return (-1);
	start += 2;
	while ((buf[start] == ' ' || buf[start] == '\t') && buf[start])
		start++;
	if (buf[start] == '\0')
		return (-1);
	return (start);
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
		start = get_start_limiter(buf, start);
		if (start == -1)
			return ;
		len = 0;
		while (buf[start + len] != ' ' && buf[start + len] != '\t'
			&& buf[start + len] != '<' && buf[start + len] != '>'
			&& buf[start + len])
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
