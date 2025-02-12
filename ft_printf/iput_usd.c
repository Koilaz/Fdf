/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iput_usd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:11:41 by lmarck            #+#    #+#             */
/*   Updated: 2024/11/15 14:48:27 by lmarck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	iput_u(va_list ap)
{
	long int	u;
	char		tab[10];
	size_t		len;
	size_t		i;

	len = 9;
	i = 0;
	u = (va_arg(ap, unsigned int));
	if (u == 0)
		return (write(1, "0", 1));
	while (u != 0)
	{
		tab[len] = (u % 10) + '0';
		u = u / 10;
		len --;
	}
	while (++len <= 9)
		i = i + write(1, &tab[len], 1);
	return (i);
}

size_t	iput_s(va_list ap)
{
	int		i;
	char	*s;

	s = va_arg (ap, char *);
	if (!s)
		return (write(1, "(null)", 6));
	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	rec_iput_d(int i)
{
	char	c;

	if (!i)
		return (0);
	c = i % 10 + '0';
	i = i / 10;
	return (rec_iput_d(i) + write (1, &c, 1));
}

size_t	iput_d( va_list ap)
{
	long int	i;
	int			len;

	len = 0;
	i = (va_arg(ap, int));
	if (i == 0)
		return (write(1, "0", 1));
	if (i == -2147483648)
		return (write(1, "-2147483648", 11));
	if (i < 0)
	{
		write(1, "-", 1);
		len++;
		i = -i;
	}
	len = len + rec_iput_d(i);
	return (len);
}
