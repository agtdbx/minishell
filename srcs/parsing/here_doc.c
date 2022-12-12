/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrenoux <ngrenoux@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:22:40 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/12 15:37:37 by ngrenoux         ###   ########.fr       */
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
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &exit_heredoc);
		tmp = readline("> ");
		if (check_buf_heredoc(tmp, limiter) == 1)
			break ;
		tmp = ft_strjoin_free_1st_p(tmp, "\n");
		to_write = ft_strjoin_free_1st_p(to_write, tmp);
		free(tmp);
	}
	free(limiter);
	return (to_write);
}

int	get_start_limiter(char *buf, int start)
{
	char	quote;

	quote = '\0';
	while ((!(buf[start] == '<' && buf[start + 1] == '<') || quote != '\0')
		&& buf[start + 1])
	{
		quote = quote_gestion(buf[start], quote);
		start++;
	}
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
	int		start;
	int		nb_cmd;

	start = 0;
	nb_cmd = 0;
	while (buf[start] && (data->pipe_error == -1 || nb_cmd < data->pipe_error))
	{
		start = get_start_limiter(buf, start);
		if (start == -1)
			return ;
		tmp = get_to_write(&start, buf);
		data->heredoc = ft_add_str(data->heredoc, tmp);
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
