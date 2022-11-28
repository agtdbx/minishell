/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:42:54 by aderouba          #+#    #+#             */
/*   Updated: 2022/11/28 15:30:10 by aderouba         ###   ########.fr       */
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

int	is_in_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	len_word(char const *s, char *sep, int i)
{
	int		len;
	char	quote;

	len = 0;
	quote = '\0';
	quote = quote_gestion(s[i], quote);
	while ((quote != '\0' ||  !is_in_char(sep, s[i + len])) && s[i + len] != '\0')
	{
		len++;
		quote = quote_gestion(s[i + len], quote);
	}
	return (len);
}

char	**ft_split_quote(char const *s, char *sep)
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
		while (is_in_char(sep, s[i]))
			i++;
		if (s[i] == '\0')
			break ;
		len = len_word(s, sep, i);
		res = ft_add_str(res, ft_substr(s, i, len));
		i += len;
	}
	return (res);
}
