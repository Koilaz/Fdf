/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:15:33 by lmarck            #+#    #+#             */
/*   Updated: 2024/11/05 12:49:26 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lit, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	if ((!big || !lit) && !len)
		return (NULL);
	if (lit[0] == '\0')
		return ((char *)big);
	while (big[j] != '\0' && j < len)
	{
		i = 0;
		while (i + j < len && big[i + j] == lit[i])
		{
			if (lit[i + 1] == '\0')
				return ((char *) &big[j]);
			i++;
		}
		j++;
	}
	return (NULL);
}
