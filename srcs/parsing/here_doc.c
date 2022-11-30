/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:22:40 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/30 10:24:26 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
