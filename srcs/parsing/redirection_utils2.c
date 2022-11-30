/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:51:43 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/30 15:02:17 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_word_redirection(char const *s, char *sep, int *i)
{
	int		len;
	char	quote;

	len = 0;
	quote = '\0';
	quote = quote_gestion(s[*i], quote);
	while (quote == '\0' && (s[*i + len] == '<' || s[*i + len] == '>')
		&& s[*i + len] != '\0')
	{
		len++;
		quote = quote_gestion(s[*i + len], quote);
	}
	while ((quote != '\0' || !is_in_char(sep, s[*i + len]))
		&& s[*i + len] != '\0')
	{
		len++;
		quote = quote_gestion(s[*i + len], quote);
	}
	return (len);
}

char	**ft_split_redirection(char *s)
{
	int		i;
	int		len;
	char	**res;

	if (s == NULL)
		return (NULL);
	res = malloc(sizeof(char *));
	if (res == NULL)
		return (NULL);
	res[0] = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		while (is_in_char(" \t", s[i]))
			i++;
		if (s[i] == '\0')
			break ;
		len = len_word_redirection(s, " \t<>", &i);
		res = ft_add_str(res, ft_substr(s, i, len));
		i += len;
	}
	return (res);
}
