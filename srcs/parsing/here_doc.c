/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:22:40 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/12 20:07:04 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fork_heredoc(char *limiter, t_data *data, int nb_cmd)
{
	int		fd;
	int		cpid;
	char	*tmp;
	char	*name;
	char	*to_write;

	to_write = malloc(sizeof(char));
	if (!to_write)
		return (-1);
	to_write[0] = '\0';
	cpid = fork();
	if (cpid == 0)
	{
		ft_lstr_free(data->paths);
		ft_lstclear(&data->env, free_var);
		if (data->heredoc)
			ft_lstr_free(data->heredoc);
		while (1)
		{
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, &exit_heredoc);
			tmp = readline("> ");
			if (g_exit_status == 130)
				break ;
			if (check_buf_heredoc(tmp, limiter) == 1)
				break ;
			tmp = ft_strjoin_free_1st_p(tmp, "\n");
			to_write = ft_strjoin_free_1st_p(to_write, tmp);
			free(tmp);
		}
		free(limiter);
		tmp = ft_itoa(nb_cmd);
		name = ft_strjoin(".heredoc", tmp);
		free(tmp);
		fd = open(name, O_RDWR | O_TRUNC | O_CREAT, 0644);
		free(name);
		if (fd == -1)
		{
			free(to_write);
			exit(1);
		}
		ft_printf_fd(to_write, fd);
		close(fd);
		free(to_write);
		exit(0);
	}
	free(to_write);
	return (cpid);
}

char	*write_in_here_doc(char *limiter, t_data *data, int nb_cmd)
{
	char	*tmp;
	char	*name;
	int		cpid;
	int		status;

	cpid = fork_heredoc(limiter, data, nb_cmd);
	waitpid(cpid, &status, 0);
	name = NULL;
	if (status == 0)
	{
		tmp = ft_itoa(nb_cmd);
		name = ft_strjoin(".heredoc", tmp);
		free(tmp);
	}
	else
		g_exit_status = 130;
	free(limiter);
	return (name);
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
		tmp = get_to_write(&start, buf, data, nb_cmd);
		if (!tmp)
		{
			ft_lstr_free(data->heredoc);
			data->heredoc = malloc(sizeof(char *));
			if (data->heredoc)
				data->heredoc[0] = NULL;
			return ;
		}
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

int	here_doc(t_data *data, t_cmd *cmd)
{
	int		res;
	char	*buf_write;

	buf_write = get_and_remove_first_heredoc(data);
	res = open(buf_write, O_RDONLY);
	cmd->heredoc = buf_write;
	return (res);
}
