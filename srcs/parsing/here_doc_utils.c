/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:46:52 by aderouba          #+#    #+#             */
/*   Updated: 2022/12/09 17:47:54 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_to_write(int *start, char *buf)
{
	int		len;
	char	quote;
	char	*tmp;

	len = 0;
	quote = '\0';
	while (((buf[*start + len] != ' ' && buf[*start + len] != '\t'
				&& buf[*start + len] != '<' && buf[*start + len] != '>')
			|| quote != '\0') && buf[*start + len])
	{
		quote = quote_gestion(buf[*start + len], quote);
		len++;
	}
	tmp = interprete_quote(ft_substr(buf, *start, len));
	tmp = write_in_here_doc(tmp);
	*start += len;
	return (tmp);
}