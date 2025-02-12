/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:59:56 by lmarck            #+#    #+#             */
/*   Updated: 2024/11/04 13:50:34 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr( const void *mblk, int sdchr, size_t size )
{
	size_t					i;
	const unsigned char		*str;

	i = 0;
	str = (const unsigned char *) mblk;
	while (i < size)
	{
		if (str[i] == (unsigned char) sdchr)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
