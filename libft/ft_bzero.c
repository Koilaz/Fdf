/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:52:43 by lmarck            #+#    #+#             */
/*   Updated: 2024/11/03 16:29:54 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *ptr, size_t n)
{
	long unsigned int	i;
	unsigned char		*ptrc;

	ptrc = (unsigned char *)ptr;
	i = 0;
	while (n > i)
	{
		ptrc[i] = '\0';
		i++;
	}
	return ;
}
