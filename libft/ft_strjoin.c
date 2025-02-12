/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:53:42 by lmarck            #+#    #+#             */
/*   Updated: 2024/11/05 12:49:55 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*nstr;
	size_t	ls1;
	size_t	ls2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	nstr = malloc(ls1 + ls2 + 1);
	if (nstr == NULL)
		return (NULL);
	i = 0;
	while (i < ls1)
	{
		nstr [i] = s1[i];
		i++;
	}
	while (i < ls1 + ls2)
	{
		nstr[i] = s2[i - ls1];
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}
