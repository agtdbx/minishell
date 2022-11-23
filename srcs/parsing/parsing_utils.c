/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:42:54 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/23 14:03:22 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	quote_gestion(char c, char quote)
{
	if (c == quote)
		quote = '\0';
	else if (c == '"' && quote == '\0')
		quote = '"';
	else if (c == '\'' && quote == '\0')
		quote = '\'';
	return (quote);
}

int	len_word(char const *s, char c, int i)
{
	int		len;
	char	quote;

	len = 0;
	quote = '\0';
	quote = quote_gestion(s[i], quote);
	while ((quote != '\0' || s[i + len] != c) && s[i + len] != '\0')
	{
		len++;
		quote = quote_gestion(s[i + len], quote);
	}
	return (len);
}

char	**ft_split_quote(char const *s, char c)
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
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		len = len_word(s, c, i);
		res = ft_add_str(res, ft_substr(s, i, len));
		i += len;
	}
	return (res);
}
