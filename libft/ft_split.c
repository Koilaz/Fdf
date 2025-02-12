/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <lmarck@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:19:34 by lmarck            #+#    #+#             */
/*   Updated: 2025/02/10 21:12:54 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			cwrd(const char *s, const char c);
static char		*strfill(char *str, const char c, char **tab, size_t n);
static void		freetab(char **tab, size_t n);
char			**ft_split(char const *s, char c);

size_t	cwrd(const char *s, const char c)
{
	size_t	i;
	size_t	n;

	n = 0;
	i = 1;
	if (s[0] == '\0' || s == NULL)
		return (0);
	if (s[0] != c)
		n++;
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			n++;
		i++;
	}
	return (n);
}

static char	*strfill(char *str, const char c, char **tab, size_t n)
{
	size_t	i;
	size_t	le;
	size_t	j;

	le = 0;
	i = 0;
	while (str[i] == c && str[i])
		i++;
	le = i;
	while (str[le] != c && str[le])
		le++;
	tab[n] = malloc((le - i + 1) * sizeof(char));
	if (!tab[n])
	{
		freetab(tab, n);
		return (NULL);
	}
	j = 0;
	while (i < le)
		tab[n][j++] = str [i++];
	tab[n][j] = '\0';
	return (&str[i]);
}

static void	freetab(char **tab, size_t n)
{
	while (n > 0)
	{
		n--;
		free(tab[n]);
	}
	free(tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	char	*str;
	size_t	nw;
	size_t	n;

	if (!s)
		return (NULL);
	nw = cwrd(s, c);
	tab = malloc((nw + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	n = 0;
	str = (char *)s;
	while (n < nw)
	{
		str = strfill(str, c, tab, n);
		if (str == NULL)
			return (NULL);
		n++;
	}
	tab[n] = NULL;
	return (tab);
}
