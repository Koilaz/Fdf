/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:40:59 by lmarck            #+#    #+#             */
/*   Updated: 2024/11/03 16:37:04 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	putabs( long int ln, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	long int	ln;

	ln = n;
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ln = -ln;
	}
	putabs(ln, fd);
}

static void	putabs( long int ln, int fd)
{
	int	tab[10];
	int	i;

	i = 9;
	while (ln != 0 && i >= 0)
	{
		tab[i] = (ln % 10) + '0';
		ln = ln / 10;
		i--;
	}
	i++;
	while (i <= 9)
	{
		ft_putchar_fd(tab[i], fd);
		i++;
	}
}
