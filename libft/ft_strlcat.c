/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:44:19 by lmarck            #+#    #+#             */
/*   Updated: 2024/11/05 12:39:38 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dl;
	size_t	sl;
	size_t	j;

	sl = ft_strlen((char *)src);
	if (!size)
		return (sl);
	dl = ft_strlen(dest);
	if (size <= dl)
		return (sl + size);
	j = 0;
	while (j < (size - dl - 1) && src[j] != '\0')
	{
		dest[j + dl] = src[j];
		j++;
	}
	dest[j + dl] = '\0';
	return (dl + sl);
}
/*#include <bsd/string.h>
int main()
{
	printf("%zu",ft_strlcat(NULL,"test",0));
	printf("%zu",strlcat(NULL,"estst",0));
	return (0);
}*/
