/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:48:58 by lmarck            #+#    #+#             */
/*   Updated: 2024/11/03 16:37:24 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset( void *pointer, int value, size_t count)
{
	long unsigned int	i;
	unsigned char		*ptr;
	unsigned char		val;

	val = (unsigned char) value;
	ptr = (unsigned char *)pointer;
	i = 0;
	while (count > i)
	{
		ptr[i] = val;
		i++;
	}
	return (pointer);
}
